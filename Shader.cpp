#include "Shader.h"

#include "Math.h"

#include <SDL/SDL.h>

#include <fstream>
#include <sstream>

Shader::Shader()
    :
    mVertexShader(0),
    mFragShader(0),
    mShaderProgram(0)
{}

Shader::~Shader()
{}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
    if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) || !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
    {
        return false;
    }

    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragShader);
    glLinkProgram(mShaderProgram);

    if (!IsValidProgram())
    {
        return false;
    }

    return true;
}

void Shader::Unload()
{
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
    glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
    GLuint location = glGetUniformLocation(mShaderProgram, name);

    glUniformMatrix4fv(location, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void Shader::SetVectorUniform(const char* name, const Vector3& vector)
{
    GLuint location = glGetUniformLocation(mShaderProgram, name);

    glUniform3fv(location, 1, vector.GetAsFloatPtr());
}

void Shader::SetFloatUniform(const char* name, float value)
{
    GLuint location = glGetUniformLocation(mShaderProgram, name);

    glUniform1f(location, value);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
    std::ifstream shaderFile(fileName);
    if (shaderFile.is_open())
    {
        std::stringstream strStream;
        strStream << shaderFile.rdbuf();
        std::string contents = strStream.str();
        const char* contentsChar = contents.c_str();

        outShader = glCreateShader(shaderType);

        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);

        if (!IsCompiled(outShader))
        {
            SDL_Log("Failed to compile shader: %s", fileName.c_str());
            return false;
        }
    }
    else
    {
        SDL_Log("Shader file not found: %s", fileName.c_str());
        return false;
    }

    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint status = GL_FALSE;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compile Failed:\n%s", buffer);
        return false;
    }

    return true;
}

bool Shader::IsValidProgram()
{
    GLint status = GL_FALSE;

    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
        SDL_Log("Shader Program failed to link:\n%s", buffer);
        return false;
    }

    return true;
}
