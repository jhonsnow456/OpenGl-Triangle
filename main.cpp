#include <iostream>
#include <cmath>
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
            
            /**
             * @brief 
             * Tell GLFW what version of OpenGL we are using 
             * In this case we are using OpenGL 3.3
             */
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

            /**
             * @brief
             * Tell GLFW we are using the CORE profile
             * So that means we only have the modern functions
             */
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            
            // Vertices coordinates
            GLfloat vertices[] = {
               -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
                0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
                0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
                -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
                0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
                0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
            };

            // Indices for vertices order
            GLuint indices[] = {
                0, 3, 5, // Lower left triangle
                3, 2, 4, // Lower right triangle
                5, 4, 1 // Upper triangle
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
                
                // Create Vertex Shader Object and get its reference
                GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
                glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach Vertex Shader source to the Vertex Shader Object
                glCompileShader(vertexShader); // Compile the Vertex Shader into machine code

                // Create Fragment Shader Object and get its reference
                GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Attach Fragment Shader source to the Fragment Shader Object
	    	    glCompileShader(fragmentShader); // Compile the Vertex Shader into machine code

                // Create Shader Program Object and get its reference
                GLuint shaderProgram = glCreateProgram();
                
                // Attach the Vertex and Fragment Shaders to the Shader Program
	            glAttachShader(shaderProgram, vertexShader); 
	            glAttachShader(shaderProgram, fragmentShader);
	            
                glLinkProgram(shaderProgram); // Wrap-up/Link all the shaders together into the Shader Program

                glDeleteShader(vertexShader);
	            glDeleteShader(fragmentShader);

                // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	            GLuint VAO, VBO, EBO;

	            // Generate the VAO and VBO with only 1 object each
	            glGenVertexArrays(1, &VAO);
	            glGenBuffers(1, &VBO);
                glGenBuffers(1, &EBO);
	
	            glBindVertexArray(VAO);// Make the VAO the current Vertex Array Object by binding it
	            
                glBindBuffer(GL_ARRAY_BUFFER, VBO);// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// Introduce the vertices into the VBO
	            
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Introduce the indices into the EBO

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	            glEnableVertexAttribArray(0); // Enable the Vertex Attribute so that OpenGL knows to use it

            	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
            	glBindBuffer(GL_ARRAY_BUFFER, 0);
	            glBindVertexArray(0);

                /**
                 * @brief 
                 * Bind the EBO to 0 so that we don't accidentally modify it
                 * MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
                 * This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
                 */
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

                // while the window is not closed
                while (!glfwWindowShouldClose(window)){
                    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Specify the color of the background
                    glClear(GL_COLOR_BUFFER_BIT); // Clean the back buffer and assign the new color to it
                    glUseProgram(shaderProgram); // Tell OpenGL which Shader Program we want to use
                    glBindVertexArray(VAO); // Bind the VAO so OpenGL knows to use it
                    // glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle using the GL_TRIANGLES primitive
                    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);// Draw primitives, number of indices, datatype of indices, index of indices
                    glfwSwapBuffers(window); // Swap the back buffer with the front buffer
                    glfwPollEvents(); // Take care of all GLFW events
                }
                
                // Delete all the objects we've created
                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
                glDeleteBuffers(1, &EBO);
                glDeleteProgram(shaderProgram);
                

            glfwDestroyWindow(window); // similarly destroying window after use.

        glfwTerminate(); // Terminate GLFW before ending the program

    return 0; 
}