#include "Renderer.h"

#include "Math.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Shader.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "VertexArray.h"

#include <GL/glew.h>
#include <SDL/SDL.h>

Renderer::Renderer(Game* game)
    :
    mGame(game),
    mMeshes({}),
    mTextures({}),
    mMeshComps({}),
    mSprites({}),
    mMeshShader(nullptr),
    mSpriteShader(nullptr),
    mSpriteVerts(nullptr),
    mView(Matrix4::Identity),
    mProjection(Matrix4::Identity),
    mScreenWidth(0.0f),
    mScreenHeight(0.0f),
    mWindow(nullptr),
    mContext()
{}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    mWindow = SDL_CreateWindow(
        "Skelkingr Game Programming",
        100,
        100,
        static_cast<int>(mScreenWidth),
        static_cast<int>(mScreenHeight),
        SDL_WINDOW_OPENGL
    );
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mContext = SDL_GL_CreateContext(mWindow);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }
    glGetError();

    if (!LoadShaders())
    {
        SDL_Log("Failed to load shaders.");
        return false;
    }

    CreateSpriteVerts();

    return true;
}

void Renderer::Shutdown()
{
    delete mSpriteVerts;

    mSpriteShader->Unload();
    delete mSpriteShader;

    mMeshShader->Unload();
    delete mMeshShader;

    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
    for (auto& tex : mTextures)
    {
        tex.second->Unload();
        delete tex.second;
    }
    mTextures.clear();

    for (auto& mesh : mMeshes)
    {
        mesh.second->Unload();
        delete mesh.second;
    }
    mMeshes.clear();
}

void Renderer::Draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    
    glDisable(GL_BLEND);

    mMeshShader->SetActive();
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

    SetLightUniforms(mMeshShader);

    for (auto mc : mMeshComps)
    {
        mc->Draw(mMeshShader);
    }

    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    mSpriteShader->SetActive();
    mSpriteVerts->SetActive();
    for (auto sprite : mSprites)
    {
        sprite->Draw(mSpriteShader);
    }

    SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
    int myFuckingDrawOrder = sprite->GetDrawOrder();

    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        if (myFuckingDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

void Renderer::AddMeshComponent(MeshComponent* mesh)
{
    mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComponent(MeshComponent* mesh)
{
    auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
    mMeshComps.erase(iter);
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
    Mesh* m = nullptr;

    auto iter = mMeshes.find(fileName);
    if (iter != mMeshes.end())
    {
        m = iter->second;
    }
    else
    {
        m = new Mesh();
        if (m->Load(fileName, this))
        {
            mMeshes.emplace(fileName, m);
        }
        else
        {
            delete m;
            m = nullptr;
        }
    }

    return m;
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
    Texture* tex = nullptr;

    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    }
    else
    {
        tex = new Texture();
        if (tex->Load(fileName))
        {
            mTextures.emplace(fileName, tex);
        }
        else
        {
            delete tex;
            tex = nullptr;
        }
    }

    return tex;
}

bool Renderer::LoadShaders()
{
    mSpriteShader = new Shader();
    if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
    {
        return false;
    }
    mSpriteShader->SetActive();

    Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
    mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

    mMeshShader = new Shader();
    if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
    {
        return false;
    }
    mMeshShader->SetActive();

    mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
    mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), mScreenWidth, mScreenHeight, 25.0f, 10000.0f);
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

    return true;
}

void Renderer::CreateSpriteVerts()
{
    float vertices[] = {
        -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f, // Top left
         0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f, // Top right
         0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f, // Bottom right
        -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f  // Bottom left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Renderer::SetLightUniforms(Shader* shader) const
{
    Matrix4 invView = mView;
    invView.Invert();
    
    shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
    
    shader->SetVectorUniform("uAmbientLight", mAmbientLight);
    
    shader->SetVectorUniform("uDirLight.mDirection", mDirLight.mDirection);
    shader->SetVectorUniform("uDirLight.mDiffuseColor", mDirLight.mDiffuseColor);
    shader->SetVectorUniform("uDirLight.mSpecColor", mDirLight.mSpecColor);
}
