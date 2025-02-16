#version 330 core

layout(location = 0) in vec3 aPos; // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color

out vec3 ourColor; // Pass the color to the fragment shader

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float size = 1.0f;

void main() {
    gl_Position = projection * view * model * vec4(aPos * size, 1.0);
    ourColor = aColor;  // Pass the color to the fragment shader
}
