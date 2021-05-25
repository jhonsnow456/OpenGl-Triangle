# adding minimum requirement of cmkae to build this project
cmake_minimum_required(VERSION 3.16.3)

# This method is to specify name of our executable file in the build folder
project(OPENENGLPROJECT)

# This method help us to identify the start point of our file or files which 
# executables are to be cretaed
add_executable(${PROJECT_NAME} main.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})


#  ********************************************************************************

# DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()


# CHECK FOR ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/submodules/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# **************************************************************************************

add_subdirectory(submodules/glfw)
add_subdirectory(submodules/glad)

# include the adder folder inside the build directory
target_include_directories(${PROJECT_NAME} 
    PUBLIC submodules/glfw/include 
)
target_include_directories(${PROJECT_NAME}
    PUBLIC submodules/glad/include
)

# link the lib files inside the Adder folder in the build directory. 
target_link_directories(${PROJECT_NAME} 
    PUBLIC submodules/glfw/src 
)
target_link_directories(${PROJECT_NAME}
    PUBLIC submodules/glad/src
)

# In the build directory add the linker file named:libadder.a 
target_link_libraries(${PROJECT_NAME} glfw glad)

# install our software in computer
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/OPENGLPROJECTConfig.h" DESTINATION include)

# Install with Cpack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${OPENGLPROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${OPENGLPROJECT_VERSION_MINOR}")
include(CPack)