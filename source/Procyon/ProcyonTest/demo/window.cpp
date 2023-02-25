#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ProcyonWindow/FWindow.h"
#include "ProcyonWindow/Device/FDevice.h"
#include "ProcyonWindow/Settings/FWindowSettings.h"
#include "ProcyonWindow/Settings/FDeviceSettings.h"

TEST(ProcyonWindow, window1) {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        loge("create GLFW window Failed");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        loge("initialize GLAD Failed");
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

namespace Demo::Window {
    struct App {
        std::unique_ptr<PrWindow::FWindow>                  window;
        std::unique_ptr<PrWindow::Device::FDevice>          device;
    };
    App app = {};


    void InitWindow() {
        // Settings
        PrWindow::Settings::FDeviceSettings deviceSettings;
        PrWindow::Settings::FWindowSettings windowSettings;
        deviceSettings.contextMajorVersion = 4;
        deviceSettings.contextMinorVersion = 6;
        windowSettings.title = "Procyon Editor";
        windowSettings.width = 800;
        windowSettings.height = 600;
        windowSettings.isMaximized = true;
        windowSettings.isFullscreen = false;

        Demo::Window::app.device = std::make_unique<PrWindow::Device::FDevice>(deviceSettings);
        app.window = std::make_unique<PrWindow::FWindow>(*(app.device), windowSettings);
        app.window->MakeCurrentContext();

        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            assert(false && "gladLoadGLLoader failed");
        }
    }

    TEST(ProcyonWindow, window) {
        InitWindow();

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);



            app.window->SwapBuffers();
            Sleep(100);
        }

    }

}

