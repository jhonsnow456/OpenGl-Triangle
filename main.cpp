#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[]){ 
        std::cout << "Welcome to code!! " << std::endl;

        glfwInit();

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGL PROJECT", NULL, NULL);
            if (window == NULL){
                std::cout << "Failed to create window!!" << std::endl;
                glfwTerminate();
                return -1;
            }

            glfwMakeContextCurrent(window);
            
                while (!glfwWindowShouldClose(window)){
                    glfwPollEvents();
                }
                
            glfwDestroyWindow(window);

        glfwTerminate();

    return 0; 
}