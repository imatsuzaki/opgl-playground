//
//  main.cpp
//  opgl-playground
//
//  Created by 松崎 出愛 on 2020/01/23.
//  Copyright © 2020 yudeayase. All rights reserved.
//

#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc, const char * argv[]) {
    // Init GLFW
    if (glfwInit() == GL_FALSE)
    {
        // Failed to init
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }
    
    GLFWwindow *const window(glfwCreateWindow(640, 480, "Hello!", NULL, NULL));
    if (window == NULL)
    {
        std::cerr << "Can't create GLFW window." << std::endl;
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
}
