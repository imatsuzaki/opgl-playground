//
//  main.cpp
//  opgl-playground
//
//  Created by 松崎 出愛 on 2020/01/23.
//  Copyright © 2020 yudeayase. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
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
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
    
    if (bufSize > 1) {
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}

// Show reult of link.
GLboolean printProgramInfoLog(GLuint program) {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;
    
    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
    
    if (bufSize > 1) {
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
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
        
        if (printShaderInfoLog(vobj, "vertex shader."))
            glAttachShader(program, vobj);
        glDeleteShader(vobj);
    }
    
    if (fsrc != NULL) {
        // create fragment shader program object
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);
        
        if (printShaderInfoLog(fobj, "fragment shader"))
            glAttachShader(program, fobj);
        glDeleteShader(fobj);
    }
    
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);
    
    if (printProgramInfoLog(program))
        return program;
    
    glDeleteProgram(program);
    return 0;
}

// Return memory where shader source file read.
// name :shader source file name
// buffer: text which read source file
bool readShaderSource(const char *name, std::vector<GLchar> &buffer){
    if (name == NULL) return false;
    
    std::ifstream file(name, std::ios::binary);
    if (file.fail()) {
        std::cerr << "Error: Can't open source file: " << name << std::endl;
        return false;
    }
    
    // Calculate file size
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());
    
    // Get file memory
    buffer.resize(length + 1);
    
    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';
    
    if (file.fail()) {
        std::cerr << "Error could not read file: " << name << std::endl;
        file.close();
        return false;
    }
    
    file.close();
    return true;
}

GLuint loadProgram(const char *vert, const char * frag) {
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(frag, fsrc));
    
    return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
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
    
//    static constexpr GLchar vsrc[] =
//      "#version 150 core\n"
//      "in vec4 position;\n"
//      "void main()\n"
//      "{\n"
//      " gl_Position = position;\n"
//      "}\n";
//    
//    static constexpr GLchar fsrc[] =
//    "#version 150 core\n"
//    "in vec4 position;\n"
//    "void main()\n"
//    "{\n"
//    " fragment = vec4(1.0, 0.0, 0.0, 1.0);\n"
//    "}\n";
    
    const GLuint program(loadProgram("point.vert", "point.frag"));
    
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
}
