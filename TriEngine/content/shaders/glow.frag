#version 330 core
in vec3 ourColor;  // Incoming color from vertex shader
out vec4 FragColor;  // Output color to framebuffer

uniform float time;

void main()
{
    float r = sin(time);
    float g = sin(time + 2.0);
    float b = sin(time + 4.0);
    FragColor = vec4(r + ourColor.x, g + ourColor.y, b + ourColor.z, 1.0);
}
