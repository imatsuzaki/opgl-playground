//
//  main.cpp
//  opgl-playground
//
//  Created by 松崎 出愛 on 2020/01/23.
//  Copyright © 2020 yudeayase. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Show result of shader object compile check
GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;
    
    GLsizei bufSize;
    
    return static_cast<GLboolean>(status);
}

// Create program object
// vsrc: program of vertex shader
// fsrc: program of fragmetn shader
GLuint createProgram(const char *vsrc, const char *fsrc){
    // empty program object
    const GLuint program(glCreateProgram());
    
    if (vsrc != NULL) {
        // create vertex shader program object
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);
        glAttachShader(program, vobj);
        glDeleteShader(vobj);
    }
    
    if (fsrc != NULL) {
        // create fragment shader program object
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);
        glAttachShader(program, fobj);
        glDeleteShader(fobj);
    }
    
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);
    
    return program;
}

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
    
    static constexpr GLchar vsrc[] =
      "#version 150 core\n"
      "in vec4 position;\n"
      "void main()\n"
      "{\n"
      " gl_Position = position;\n"
      "}\n";
    
    static constexpr GLchar fsrc[] =
    "#version 150 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    " fragment = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";
    
    const GLuint program(createProgram(vsrc, fsrc));
    
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
}
