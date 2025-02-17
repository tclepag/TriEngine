#version 330 core
in vec3 ourColor;  // Incoming color from vertex shader
out vec4 FragColor;  // Output color to framebuffer

uniform float TIME; // Use glfwTime to animate

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // Use the color passed from the vertex shader
}
