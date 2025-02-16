#version 330 core
in vec3 ourColor;  // Incoming color from vertex shader
out vec4 FragColor;  // Output color to framebuffer

void main()
{
    FragColor = vec4() * vec4(ourColor, 1.0);  // Use the color passed from the vertex shader
}
