#pragma once
#include <iostream>
#include <GL/glew.h> // OpenGL extended
#include <GLFW/glfw3.h> // multi platform for OpenGL

class Window {
    
    GLFWwindow *const window;
    
public:
    Window(
           int width = 640,
           int height = 480,
           const char *title = "Hello"
           ) : window(glfwCreateWindow(width, height, title, NULL, NULL))
    {
        if (window == NULL) {
            std::cerr << "Can't create GLFW window." << std::endl;
            exit(1);
        }
        
        glfwMakeContextCurrent(window);
        
        // GLEWの初期化
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Can't initialize glew." << std::endl;
            exit(1);
        }
        
        // 垂直同期のタイミングを待つ
        glfwSwapInterval(1);
    }
    
    virtual ~Window()
    {
        glfwDestroyWindow(window);
    }
    
    explicit operator bool(){
        glfwWaitEvents();
        return !glfwWindowShouldClose(window);
    }
    
    void swapBuffers() const
    {
        glfwSwapBuffers(window);
    }
    
    static void resize(GLFWwindow *const window, int width, int height)
    {
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);
    }
};
