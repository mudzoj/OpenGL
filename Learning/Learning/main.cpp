#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h" // Include your shader class
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(){ 
   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL); //define window box
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    

    //LINK SHADERS - Shader Program Initialization
    // build and compile our shader program
    // ------------------------------------
        Shader shaderProgram("3.3.shader.vs.txt", "3.3.shader.fs.txt"); //All shader program work done in Shader.cpp now!
  


//***********************************************************************************************************************************
//**************************************************SETUP Vertex BUFFER and DATA******************************************************
//************************************************************************************************************************************
    float vertices[] = {
     //positions          //colors
      0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // top right
     -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top left

    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        1, 2, 3    // second triangle
    };

    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    //Copy our vertices array into a buffer for opengl to use
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // set vertex attributes pointers
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //pos attribute     //attribute location,amount of vars,type of vars,normalizeval?,size of each stride,starting ptr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


//************************************************************************************************************************************
//**************************************************MAIN GAME RENDER LOOP*************************************************************
//************************************************************************************************************************************

    while (!glfwWindowShouldClose(window)){      //THE MAIN RENDER LOOP!!!!!!
                                               
        processInput(window); //close window based off user enterring 'esc' KEY

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        

        shaderProgram.use();

        int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //check and call swap buffers and events
        glfwSwapBuffers(window);   
        glfwPollEvents();        //Checks for any user input and triggers and calls corresponding functions.

        
    }
      
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height); //this is the actual window where rendering will happen!
                                    //Can be smaller than glfwCreateWindow() window size.
}


void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
