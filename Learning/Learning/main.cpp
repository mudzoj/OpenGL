#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h" // Include your shader class
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "stb_image.h"

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
  
    
    glEnable(GL_DEPTH_TEST);


//***********************************************************************************************************************************
//**************************************************SETUP Vertex BUFFER and DATA******************************************************
//************************************************************************************************************************************

    float vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f
    };

  


    unsigned int indices[] = {  // note that we start from 0!
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11,
        12,13,14,
        15,16,17,
        18,19,20,
        21,22,23,
        24,25,26,
        27,28,29,
        30,31,32,
        33,34,35
    };

    unsigned int VBO,VAO,EBO;
    //Copy our vertices array into a buffer for opengl to use
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // set vertex attributes pointers
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    //pos attribute     //attribute location,amount of vars,type of vars,normalizeval?,size of each stride,starting ptr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture1,texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("C:/Users/mudzo/Desktop/Coding/LearningOpenGL/Learning/textures/container.jpg", &width, &height, &nrChannels, 0); 
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture 2
    // ---------
    glGenTextures(1, &texture2); 
    glBindTexture(GL_TEXTURE_2D, texture2);  
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("C:/Users/mudzo/Desktop/Coding/LearningOpenGL/Learning/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    shaderProgram.use();  // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture1"), 0); 
    // or set it via the texture class
    shaderProgram.setInt("texture2", 1); 

    unsigned int transformLoc = glGetUniformLocation(shaderProgram.ID, "transform");
    int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
    int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
    int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
    



//************************************************************************************************************************************
//**************************************************MAIN GAME RENDER LOOP*************************************************************
//************************************************************************************************************************************

    while (!glfwWindowShouldClose(window)){      //THE MAIN RENDER LOOP!!!!!!
                                               
        processInput(window); //close window based off user enterring 'esc' KEY

     
        
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // render container
        shaderProgram.use();
        glBindVertexArray(VAO);


        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f)*10, glm::vec3(0.5f, 1.0f, 0.0f));

            float angle = 20.0f * i;

            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        


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
