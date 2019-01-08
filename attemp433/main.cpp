#include "libs.h"

Vertex vertices[] =
{
    // position                     // color                    // texture              // normal
    glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),  glm::vec3(0.f, 0.f, 1.f),
    glm::vec3(-0.5f, -0.5f, 0.f),    glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),   glm::vec3(0.f, 0.f, 1.f),
    glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(1.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, 1.f),
    glm::vec3(0.5f, 0.5f, 0.f),    glm::vec3(0.f, 1.f, 1.f),   glm::vec2(1.f, 1.f),    glm::vec3(0.f, 0.f, 1.f)
};
unsigned int numberOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = 
{
    0, 1, 2, 3, 0, 2
};
unsigned int numberOfIndices = sizeof(indices) / sizeof(GLuint);

void updateInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void frameBufferResizeCallback(GLFWwindow* window, int fbW, int gbH)
{
    glViewport(0, 0, fbW, fbW);
}

void updateInput(GLFWwindow* window, Mesh &mesh)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        mesh.move(glm::vec3(0.f, 0.f, 0.01f));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        mesh.move(glm::vec3(0.f, 0.f, -0.01f));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        mesh.move(glm::vec3(0.01f, 0.f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        mesh.rotate(glm::vec3(0.f, -1.f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        mesh.rotate(glm::vec3(0.f, 1.f, 0.f));
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        mesh.scale(glm::vec3(0.1f));
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        mesh.scale(glm::vec3(-0.1f));
    }
}

int main()
{
    glfwInit();

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "attempt433", NULL, NULL);

    glfwGetFramebufferSize(window, &frameBufferHeight, &frameBufferHeight);
    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);

    //glViewport(0, 0, frameBufferHeight, frameBufferHeight);

    glfwMakeContextCurrent(window);

    // init glew (needs context and window)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error::main.cpp::glew_init_failed" << std::endl;
        glfwTerminate();
    }

    // OpenGl options
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE); // don't draw what's not shown
    glCullFace(GL_BACK); // cull face is the back
    glFrontFace(GL_CCW); // the back is when vertices point counter clockwise

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // shaders init
    Shader core_program("vertex_core.glsl", "fragment_core.glsl");

    Mesh test(
        &Quad(),
        glm::vec3(0.f),
        glm::vec3(0.f), 
        glm::vec3(1.f)
    );

    // textures
    Texture texture0("images/test.png", GL_TEXTURE_2D, 0);
    Texture texture1("images/brick.png", GL_TEXTURE_2D, 1);

    Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture0.getTextureUnit(), texture1.getTextureUnit());

    glm::vec3 camPosition = glm::vec3(0.f, 0.f, 1.f);
    glm::vec3 worldUp(0.f, 1.f, 0.f);
    glm::vec3 camFront(0.f, 0.f, -1.f);
    glm::mat4 ViewMatrix(1.f);
    ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

    float fov = 90.f;
    float nearPlane = 0.1f;
    float farPlane = 1000.f;
    glm::mat4 ProjectionMatrix(1.f);
    ProjectionMatrix = glm::perspective(
        glm::radians(fov),
        static_cast<float>(frameBufferWidth) / frameBufferHeight,
        nearPlane,
        farPlane
    );

    // lights

    glm::vec3 lightPos0(0.f, 0.f, 1.f);

    core_program.setMat4fv(ViewMatrix, "ViewMatrix");
    core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

    core_program.setVec3f(lightPos0, "lightPos0");
    core_program.setVec3f(camPosition, "cameraPos");

    // main loop

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        updateInput(window, test);

        // update

        updateInput(window);

        // clear

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // draw

        core_program.set1i(texture0.getTextureUnit(), "texture0");
        core_program.set1i(texture1.getTextureUnit(), "texture1");
        material0.sendToShader(core_program);

        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
        ProjectionMatrix = glm::mat4(1.f);
        ProjectionMatrix = glm::perspective(
            glm::radians(fov),
            static_cast<float>(frameBufferWidth) / frameBufferHeight,
            nearPlane,
            farPlane
        );
        core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

        core_program.use();

        texture0.bind();
        texture1.bind();

        test.render(&core_program);

        glfwSwapBuffers(window);
        glFlush();

        glBindVertexArray(0);
        core_program.unuse();
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // end
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
