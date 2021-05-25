#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[]){ 
        std::cout << "Welcome to code!! " << std::endl;

        glfwInit(); // initializing the glew

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            /**
             * @brief Here we are basically initializing the window 
             * and creating a window object.
             */
            GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGL PROJECT", NULL, NULL);
            if (window == NULL){
                std::cout << "Failed to create window!!" << std::endl;
                glfwTerminate();
                return -1;
            }

            glfwMakeContextCurrent(window);

                gladLoadGL();
                glViewport(0, 0, 800, 800);

                glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // this is the color stored in the back
                glClear(GL_COLOR_BUFFER_BIT); // color stored in the foregoround.
                glfwSwapBuffers(window); // swapping the buffer so as after each rendering our screen get clear

                while (!glfwWindowShouldClose(window)){
                    glfwPollEvents();
                }
                
            glfwDestroyWindow(window);

        glfwTerminate();

    return 0; 
}