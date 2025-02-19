#version 330 core
in vec3 ourColor;  // Incoming color from vertex shader
out vec4 FragColor;  // Output color to framebuffer

in vec2 TexCoord;
uniform sampler2D texture1;

void main()
{
    vec4 texColor = texture(texture1, TexCoord);
    vec4 finalColor = mix(texColor, vec4(ourColor, 1.0), 0.5);
    //FragColor = texColor;  // Use the color passed from the vertex shader
    FragColor = texture(texture1, TexCoord);
}
