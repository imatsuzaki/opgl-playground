//
//  main.cpp
//  opgl-playground
//
//  Created by 松崎 出愛 on 2020/01/23.
//  Copyright © 2020 yudeayase. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(int argc, const char * argv[]) {
    // Init GLFW
    if (glfwInit() == GL_FALSE)
    {
        // Failed to init
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }
    
    atexit(glfwTerminate);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow *const window(glfwCreateWindow(640, 480, "Hello!", NULL, NULL));
    if (window == NULL)
    {
        std::cerr << "Can't create GLFW window." << std::endl;
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Can't initialize glew." << std::endl;
        return 1;
    }
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
}
