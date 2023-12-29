#version 330

uniform mat4 uWorld;
uniform mat4 uViewProj;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoords;

out vec2 fragTexCoords;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * uWorld * uViewProj;
	fragTexCoords = inTexCoords;
}