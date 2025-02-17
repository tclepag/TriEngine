#version 330 core
in vec3 ourColor;  // Incoming color from vertex shader
out vec4 FragColor;  // Output color to framebuffer

uniform float time;

void main()
{
    float r = sin(time * 2.0) * sin(time * 1.5);
    float g = sin(time * 4.0) * sin(time * 1.5);
    float b = sin(time * 5.0) * sin(time * 1.5);
    FragColor = vec4(r + ourColor.x, g + ourColor.y, b + ourColor.z, 1.0);
}
