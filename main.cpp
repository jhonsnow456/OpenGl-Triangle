#include <iostream>
#include <cmath>
// #include <OPENGLPROJECTConfig.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "void main()\n"
                                "{\n"
                                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                "}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
                                "out vec4 FragColor;\n"
                                "void main()\n"
                                "{\n"
                                "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                "}\n\0";

int main(int argc, char** argv){ 
        std::cout << "Welcome to code!! " << std::endl;
        // std::cout << argv[0] << " Version: " << OPENGLPROJECT_VERSION_MAJOR << "." << OPENGLPROJECT_VERSION_MINOR << '\n';

        glfwInit(); // initializing the glew

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            

            GLfloat vertices[] = {
                -0.5f, -0.5f * float(sqrt(3)) / 3 , 0.0f,
                0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
                0.0f, 0.5f * float(3)  / 3, 0.0f
            };
            /**
             * @brief Here we are basically initializing the window 
             * and creating a window object.
             */
            GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGL PROJECT TRIANGLE", NULL, NULL);
            if (window == NULL){
                std::cout << "Failed to create window!!" << std::endl;
                glfwTerminate();
                return -1;
            }

            glfwMakeContextCurrent(window); // introducing window to current context

                gladLoadGL(); // Load glad to configure opengl
                glViewport(0, 0, 800, 800);
                

                GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
                glCompileShader(vertexShader);

                GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	    	    glCompileShader(fragmentShader);

                GLuint shaderProgram = glCreateProgram();
	            glAttachShader(shaderProgram, vertexShader);
	            glAttachShader(shaderProgram, fragmentShader);
	            glLinkProgram(shaderProgram);

                glDeleteShader(vertexShader);
	            glDeleteShader(fragmentShader);

                // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	            GLuint VAO, VBO;

	            // Generate the VAO and VBO with only 1 object each
	            glGenVertexArrays(1, &VAO);
	            glGenBuffers(1, &VBO);
	
	            glBindVertexArray(VAO);// Make the VAO the current Vertex Array Object by binding it
	            glBindBuffer(GL_ARRAY_BUFFER, VBO);// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// Introduce the vertices into the VBO
	            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	            glEnableVertexAttribArray(0); // Enable the Vertex Attribute so that OpenGL knows to use it

            	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
            	glBindBuffer(GL_ARRAY_BUFFER, 0);
	            glBindVertexArray(0);

                // while the window is not closed
                while (!glfwWindowShouldClose(window)){
                    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT);
                    glUseProgram(shaderProgram);
                    glBindVertexArray(VAO);
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                    glfwSwapBuffers(window);
                    glfwPollEvents();
                }

                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
                glDeleteProgram(shaderProgram);
                
            glfwDestroyWindow(window); // similarly destroying window after use.

        glfwTerminate();

    return 0; 
}