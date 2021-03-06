#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat4 proj;

void main()
{
   gl_Position = proj*transform*vec4(aPos, 1.0);
}