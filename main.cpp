#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,     1.0f, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     1.0f, 0.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.0f, 1.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.0f, 1.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.0f, 0.0f, 1.0f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

int w = 800;
int h = 600;

float aspectRatio = (float)w / (float)h;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Update the viewport
    glViewport(0, 0, width, height);
    w = width;
    h = height;

    aspectRatio = (float)w / (float)h;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(w, h, "TriEngine", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    int ico_width, ico_height, channels;
    unsigned char* pixels = stbi_load("content/images/app.bmp", &ico_width, &ico_height, &channels, STBI_rgb_alpha);
    if (pixels == nullptr) {
        std::cout << "Failed to load image" << std::endl;
        stbi_image_free(pixels);
        return -1;
    }

    GLFWimage icon;
    icon.width = ico_width;
    icon.height = ico_height;
    icon.pixels = pixels;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetWindowIcon(window, 1, &icon);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    GLuint vao, vbo, ebo;


    glGenBuffers(1, &ebo); // Create Element Buffer Object
    glGenVertexArrays(1, &vao); // Create Vertex Array Object
    glGenBuffers(1, &vbo); // Create Vertex Buffer Object

    glBindVertexArray(vao); // Bind the Vertex Array Object


    // Bind Vertex Buffer Object and transfer vertex data to the Vertex Array Object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind Element Buffer Object and load our indices.
    // Helpful since instead of specifying vertice position,
    // we use ints and OpenGL just gets the vertex position by finding it with the index
    // Like: vertices[index]
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture Coordinate Attribute
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);

    // Unbind Vertex Buffer Object and Vertex Array Object
    // Good practice to unbind after creation
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create Shader Program
    GLuint program = glCreateProgram();

    GLint success;
    char infoLog[512];

    std::string vertexCode = get_file_contents("content/shaders/default.vert");
    std::string fragmentCode = get_file_contents("content/shaders/glow.frag");

    const char* vertexShaderSource = vertexCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        return -1;
    }

    const char* fragmentShaderSource = fragmentCode.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        return -1;
    }


    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        return -1;
    }

    glUseProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        // Clear the background buffer and set the background color to black
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Use our shader program
        glUseProgram(program);

        float currentTime = glfwGetTime();
        float rotate_speed = 150.0f;
        float float_speed = 1.0f;
        float float_distance = 0.2f;

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
        projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
        model = glm::translate(model, glm::vec3(0.0f, (sin(currentTime * float_speed) * float_distance) - 1.0f, -5.0f));
        model = glm::rotate(model, currentTime * glm::radians(rotate_speed), glm::vec3(0.0f, 0.5, 0));

        float origin_scale = 2.0f;
        float size = 0.1;
        float scale_speed = 1.5f;
        float scale_distance = 0.9f;

        size = origin_scale + sin(currentTime * scale_speed) * scale_distance;

        glUniformMatrix4fv(
            glGetUniformLocation(program, "model"),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(program, "view"),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(program, "projection"),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glUniform1f(
            glGetUniformLocation(program, "time"),
            currentTime
        );

        glUniform1f(
            glGetUniformLocation(program, "size"),
            size
        );


        // Bind Vertex Array Object to draw the object
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, nullptr);  // Use indices to draw
        glBindVertexArray(0);

        // The drawing was done in the background buffer
        // We swap our buffers to show the results
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}