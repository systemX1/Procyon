
#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ProcyonRendering/Resources/FShader.h"
#include "ProcyonRendering/Buffer/TVertexBuffer.h"
#include "ProcyonRendering/Buffer/FVertexArray.h"
#include "ProcyonRendering/Buffer/FElementBuffer.h"


#include "ProcyonWindow/FWindow.h"
#include "ProcyonWindow/Device/FDevice.h"
#include "ProcyonWindow/Settings/FWindowSettings.h"
#include "ProcyonWindow/Settings/FDeviceSettings.h"


namespace Demo::Triangle {
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

        app.device = std::make_unique<PrWindow::Device::FDevice>(deviceSettings);
        app.window = std::make_unique<PrWindow::FWindow>(*(app.device), windowSettings);
        app.window->MakeCurrentContext();


        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            assert(false && "gladLoadGLLoader failed");
        }
    }

    // hello, triangle
    TEST(ProcyonEditor, triangle1) {
        fmtlog::setLogLevel(fmtlog::DBG);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\TriangleFS.glsl)");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        constexpr float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
        };

        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(static_cast<GLuint>(0), static_cast<GLint>(3), static_cast<GLenum>(PrRendering::Buffer::EType::Float), GL_FALSE, static_cast<GLsizei>(3 * sizeof(float)), reinterpret_cast<const GLvoid*>(0));

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        //glBindVertexArray(0);

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            triangleShader.UseProgram();
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glDrawArrays(GL_TRIANGLES, 0, 3);

            app.window->SwapBuffers();
        }
    }

    // hello, triangle
    TEST(ProcyonEditor, triangle2) {
        fmtlog::setLogLevel(fmtlog::DBG);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\TriangleFS.glsl)");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
             0.5f, -0.5f, 0.0f, // right
             0.0f,  0.5f, 0.0f  // top
        };
        
        PrRendering::Buffer::FVertexArray vao;
        PrRendering::Buffer::TVertexBuffer<float> vbo(vertices, sizeof(vertices)/ sizeof(float));
        vao.BindAttribute(vbo, 0, 3, PrRendering::Buffer::EType::Float, 3 * sizeof(float), 0);

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            triangleShader.UseProgram();
            vao.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            app.window->SwapBuffers();
        }
    }

    // hello, rectangle
    TEST(ProcyonEditor, rectangle1) {
        fmtlog::setLogLevel(fmtlog::DBG);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\TriangleFS.glsl)");

        float vertices[] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
        };
        unsigned int indices[] = {
            // 注意索引从0开始! 
            // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
            // 这样可以由下标代表顶点组合成矩形

            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
        };

        uint32_t EBO;
        glGenBuffers(1, &EBO);

        // bind: vao->vbo->ebo
        PrRendering::Buffer::FVertexArray vao;
        PrRendering::Buffer::TVertexBuffer<float> vbo(vertices, sizeof(vertices) / sizeof(float));
        vao.BindAttribute(vbo, 0, 3, PrRendering::Buffer::EType::Float, 3 * sizeof(float), 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            triangleShader.UseProgram();
            vao.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            app.window->SwapBuffers();
        }
    }

    // hello, rectangle
    TEST(ProcyonEditor, rectangle2) {
        fmtlog::setLogLevel(fmtlog::DBG);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\TriangleFS.glsl)");

        float vertices[] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
        };
        uint32_t indices[] = {
            // 注意索引从0开始! 
            // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
            // 这样可以由下标代表顶点组合成矩形

            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
        };


        // bind: vao->vbo->ebo
        PrRendering::Buffer::FVertexArray vao;
        PrRendering::Buffer::TVertexBuffer<float> vbo(vertices, sizeof(vertices) / sizeof(float));
        vao.BindAttribute(vbo, 0, 3, PrRendering::Buffer::EType::Float, 3 * sizeof(float), 0);

        PrRendering::Buffer::FElementBuffer ebo(indices, sizeof(indices) / sizeof(uint32_t));


        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            triangleShader.UseProgram();
            vao.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            app.window->SwapBuffers();
        }
    }
}