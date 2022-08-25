

#include "gl++/glfw_glew_init.hpp"
#include "gl++/control.hpp" 
#include "gl++/geometry.hpp"
#include "gl++/shader.hpp"




int main()
{
    GLFWwindow* window = glfw_GLEW_init();
    initControl(window);
    Shader shaderProgram("recources/shaders/Shader.vert", "recources/shaders/Shader.frag");
    
    CubeObject cube(vertexCoords(-1.0f, -1.0f, 1.0f), vertexCoords(-0.8f, 0.5f, -0.5f));
    CubeObject cube2(vertexCoords(-0.5f, 0.0f, 0.5f), vertexCoords(0.0f, 0.5f, -0.5f));
    auto vertices = cube.getVertices();
    auto indices = cube.getIndices();

    


    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, cube.verticesBufferSize, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indicesBufferSize, indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

    
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glm::mat4 model(1.f);
        glm::mat4 view(1.f);
        glm::mat4 projection(1.f);
        model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 50.f), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        projection = glm::perspective(glm::radians(45.f), (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 100.0f);

        GLint modelLoc = glGetUniformLocation(shaderProgram.Program, "model");
        GLint viewLoc = glGetUniformLocation(shaderProgram.Program, "view");
        GLint projLoc = glGetUniformLocation(shaderProgram.Program, "projection"); 

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); 
        GLint colorLoc = glGetUniformLocation(shaderProgram.Program, "color");
        glUniform4f(colorLoc, 1.0, 0.0, 0.0, 1.0);
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, NULL);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        glfwSwapBuffers(window);
        
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}




