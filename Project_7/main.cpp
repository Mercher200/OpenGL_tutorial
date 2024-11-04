#include "glew.h"
#include "glfw3.h"

#include <iostream>

#include "VertexBuffer.h"
#include "indexBuffer.h"
#include "VertexArray.h" 
#include "Shader.h" 
#include "VertexBufferLayout.h"
#include "Renderer.h" 
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "backend/imgui_impl_opengl3.h"
#include "backend/imgui_impl_glfw.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 540, "Hello", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK) std::cout << "ERROR !!!" << std::endl;

    std::cout<<glGetString(GL_VERSION) <<std::endl;
{
    float positions[] = { //фактический буфер 
        100.0f , 100.0f , 0.0f, 0.0f,
        200.0f , 200.0f , 1.0f, 0.0f,
        200.0f , 200.0f , 1.0f, 1.0f,
        100.0f , 100.0f , 0.0f, 1.0f
    }; 

    // индексный буффер
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    }; // индексация фактичесного буффера 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //unsigned int vao;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao); //привязка массива вершин и указание его индефикатора

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    indexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    glm::mat4 mvp = proj * view * model;

    Shader shader("Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.SetUniformMat4f("u_MVP", mvp);

    Texture texture("src/logo.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Bind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    float red = 0.0f;
    float increment = 0.05f;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();   

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame(); 

        shader.Bind();
        shader.SetUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);

        renderer.Draw(va, ib, shader);

        if(red > 1.0f) increment = -0.05f; else if(red < 0.0f) increment = 0.05f;
        red+=increment;

        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    

}    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}