#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 look;

void main()
{
   gl_Position = proj*look*view*transform*vec4(aPos, 1.0);
}
