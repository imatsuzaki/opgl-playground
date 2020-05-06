#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main() {
    // GLFW を初期化する
    if (glfwInit() == GL_FALSE) {
        // 初期化に失敗した
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }

    // プログラム終了時の処理を登録する
    atexit(glfwTerminate);

    // OpenGL Version 3.2 Core Profile を選択する
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *const window = glfwCreateWindow(640, 480, "Hello", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Can't make window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);


    // 背景色を指定する
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // プログラムオブジェクトを作成する
   
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        glClear(GL_COLOR_BUFFER_BIT);

    
        glfwSwapBuffers(window);

        glfwWaitEvents();
    }
}
