
#include "pch.h"

#include "ProcyonRendering/Resources/FShader.h"
#include "ProcyonRendering/Buffer/FVertexBuffer.h"
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
    TEST(ProcyonRendering, triangle1) {
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
    TEST(ProcyonRendering, triangle2) {
        fmtlog::setLogLevel(fmtlog::DBG);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\TriangleFS.glsl)");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
             0.5f, -0.5f, 0.0f, // right
             0.0f,  0.5f, 0.0f  // top
        };
        
        PrRendering::Buffer::FVertexArray vao;
        PrRendering::Buffer::FVertexBuffer vbo(vertices, sizeof(vertices)/ sizeof(float));
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
    TEST(ProcyonRendering, rectangle1) {
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
        PrRendering::Buffer::FVertexBuffer vbo(vertices, sizeof(vertices) / sizeof(float));
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
    TEST(ProcyonRendering, rectangle2) {
        fmtlog::setLogLevel(fmtlog::DBG);
        //fmtlog::setLogFile(stderr, false);

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
        PrRendering::Buffer::FVertexBuffer vbo(vertices, sizeof(vertices) / sizeof(float));
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

    // hello, rectangle
    TEST(ProcyonRendering, rectangle3) {
        fmtlog::setLogLevel(fmtlog::DBG);
        //fmtlog::setLogFile(stderr, false);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\test\ColorfulRectangleVS.glsl)", R"(..\..\..\asset\shader\test\ColorfulRectangleFS.glsl)");

        float vertices[] = {
            0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f, // 右上角
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // 右下角
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // 左下角
            -0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 1.0f, // 左上角
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
        PrRendering::Buffer::FVertexBuffer vbo(vertices, sizeof(vertices) / sizeof(float));
        vao.BindAttribute(vbo, 0, 3, PrRendering::Buffer::EType::Float, 6 * sizeof(float), 0);
        vao.BindAttribute(vbo, 1, 3, PrRendering::Buffer::EType::Float, 6 * sizeof(float), 3 * sizeof(float));

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


    // hello, rectangle
    TEST(ProcyonRendering, rectangle4) {
        fmtlog::setLogLevel(fmtlog::DBG);
        //fmtlog::setLogFile(stderr, false);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\test\ColorfulRectangleVS.glsl)", R"(..\..\..\asset\shader\test\ColorfulRectangleFS.glsl)");

        float vertices[] = {
            0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f, // 右上角
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // 右下角
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // 左下角
            -0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 1.0f, // 左上角
        };
        uint32_t indices[] = {
            // 注意索引从0开始! 
            // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
            // 这样可以由下标代表顶点组合成矩形
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
        };

        // bind: vao->vbo->ebo
        const PrRendering::Buffer::FVertexBufferLayouts vertexBufferLayouts{
            PrRendering::Buffer::FVertexBufferLayout(0, 3, 6, false),
            PrRendering::Buffer::FVertexBufferLayout(1, 3, 6, false),
        };
        const PrRendering::Buffer::FVertexBuffer vbo(vertices, sizeof(vertices) / sizeof(float), vertexBufferLayouts);
        const PrRendering::Buffer::FVertexArray vao(vbo);
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

    // hello, rectangle
    TEST(ProcyonRendering, rectangle5) {
        fmtlog::setLogLevel(fmtlog::DBG);
        //fmtlog::setLogFile(stderr, false);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\test\ColorfulRectangle2VS.glsl)", R"(..\..\..\asset\shader\test\ColorfulRectangle2FS.glsl)");

        float vertices[] = {
            0.5f, 0.5f, 0.0f,  // 右上角
            0.5f, -0.5f, 0.0f, // 右下角
            -0.5f, -0.5f, 0.0f,// 左下角
            -0.5f, 0.5f, 0.0f, // 左上角
        };
        uint32_t indices[] = {
            // 注意索引从0开始! 
            // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
            // 这样可以由下标代表顶点组合成矩形
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
        };

        // bind: vao->vbo->ebo
        const PrRendering::Buffer::FVertexBufferLayouts vertexBufferLayouts{
            PrRendering::Buffer::FVertexBufferLayout(0, 3, 3, false),
        };
        const PrRendering::Buffer::FVertexBuffer vbo(vertices, sizeof(vertices) / sizeof(float), vertexBufferLayouts);
        const PrRendering::Buffer::FVertexArray vao(vbo);
        PrRendering::Buffer::FElementBuffer ebo(indices, sizeof(indices) / sizeof(uint32_t));

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            triangleShader.UseProgram();
            const int    loc        = glGetUniformLocation(triangleShader.GetID(), "color");
            const float timeValue  = glfwGetTime() + 0.5;
            const float redValue = (sin(timeValue));
            const float greenValue = (cos(timeValue));
            const float blueValue = (atan(timeValue));
            glUniform3f(loc, redValue, greenValue, blueValue);

            vao.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            app.window->SwapBuffers();
            Sleep(50);
        }
    }

    // ex1 Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data
    TEST(ProcyonRendering, ex1) {
        fmtlog::setLogLevel(fmtlog::DBG);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\TriangleFS.glsl)");

        float vertices[] = {
            // first triangle
            -0.9f, -0.5f, 0.0f,  // left 
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top 
            // second triangle
             0.0f, -0.5f, 0.0f,  // left
             0.9f, -0.5f, 0.0f,  // right
             0.45f, 0.5f, 0.0f   // top 
        };

        // bind: vao->vbo->ebo
        PrRendering::Buffer::FVertexArray vao;
        PrRendering::Buffer::FVertexBuffer vbo(vertices, sizeof(vertices) / sizeof(float));
        vao.BindAttribute(vbo, 0, 3, PrRendering::Buffer::EType::Float, 3 * sizeof(float), 0);

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            triangleShader.UseProgram();
            vao.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);

            app.window->SwapBuffers();
        }
    }

    // ex2 Now create the same 2 triangles using two different VAOs and VBOs for their data
    TEST(ProcyonRendering, ex2) {
        fmtlog::setLogLevel(fmtlog::DBG);

        InitWindow();
        const PrRendering::Resources::FShader triangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\TriangleFS.glsl)");

        constexpr float firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // left 
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top 
        };
        constexpr float secondTriangle[] = {
                0.0f, -0.5f, 0.0f,  // left
                0.9f, -0.5f, 0.0f,  // right
                0.45f, 0.5f, 0.0f   // top 
        };

        // bind: vao->vbo->ebo
        std::vector<std::unique_ptr<PrRendering::Buffer::FVertexArray> > vao;
        vao.reserve(2);
        auto vao1 = std::make_unique<PrRendering::Buffer::FVertexArray>();
        auto vao2 = std::make_unique<PrRendering::Buffer::FVertexArray>();

        vao.emplace_back(std::move(vao1));
        vao.emplace_back(std::move(vao2));

        std::vector<std::unique_ptr<PrRendering::Buffer::FVertexBuffer > > vbo;
        auto vbo1 = std::make_unique<PrRendering::Buffer::FVertexBuffer >(firstTriangle, sizeof(firstTriangle) / sizeof(float));
        auto vbo2 = std::make_unique<PrRendering::Buffer::FVertexBuffer >(secondTriangle, sizeof(secondTriangle) / sizeof(float));
        vbo.emplace_back(std::move(vbo1));
        vbo.emplace_back(std::move(vbo2));

        vao.at(0)->BindAttribute(*vbo.at(0), 0, 3, PrRendering::Buffer::EType::Float, 3 * sizeof(float), 0);
        vao.at(1)->BindAttribute(*vbo.at(1), 0, 3, PrRendering::Buffer::EType::Float, 3 * sizeof(float), 0);

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            triangleShader.UseProgram();
            vao.at(0)->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
            vao.at(1)->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            app.window->SwapBuffers();
        }
    }

    // ex3 Create two shader programs where the second program uses a different fragment shader that outputs the color yellow; draw both triangles again where one outputs the color yellow
    TEST(ProcyonRendering, ex3) {
        fmtlog::setLogLevel(fmtlog::DBG);

        InitWindow();
        const PrRendering::Resources::FShader redTriangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\TriangleFS.glsl)");
        const PrRendering::Resources::FShader yellowTriangleShader(R"(..\..\..\asset\shader\TriangleVS.glsl)", R"(..\..\..\asset\shader\test\YellowTriangleFS.glsl)");

        constexpr float firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // left 
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top 
        };
        constexpr float secondTriangle[] = {
                0.0f, -0.5f, 0.0f,  // left
                0.9f, -0.5f, 0.0f,  // right
                0.45f, 0.5f, 0.0f   // top 
        };

        // bind: vao->vbo->ebo
        std::vector<std::unique_ptr<PrRendering::Buffer::FVertexArray> > vao;
        vao.reserve(2);
        auto vao1 = std::make_unique<PrRendering::Buffer::FVertexArray>();
        auto vao2 = std::make_unique<PrRendering::Buffer::FVertexArray>();

        vao.emplace_back(std::move(vao1));
        vao.emplace_back(std::move(vao2));

        std::vector<std::unique_ptr<PrRendering::Buffer::FVertexBuffer> > vbo;
        auto vbo1 = std::make_unique<PrRendering::Buffer::FVertexBuffer >(firstTriangle, sizeof(firstTriangle) / sizeof(float));
        auto vbo2 = std::make_unique<PrRendering::Buffer::FVertexBuffer >(secondTriangle, sizeof(secondTriangle) / sizeof(float));
        vbo.emplace_back(std::move(vbo1));
        vbo.emplace_back(std::move(vbo2));

        vao.at(0)->BindAttribute(*vbo.at(0), 0, 3, PrRendering::Buffer::EType::Float, 3 * sizeof(float), 0);
        vao.at(1)->BindAttribute(*vbo.at(1), 0, 3, PrRendering::Buffer::EType::Float, 3 * sizeof(float), 0);

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            redTriangleShader.UseProgram();
            vao.at(0)->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            yellowTriangleShader.UseProgram();
            vao.at(1)->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            app.window->SwapBuffers();
        }
    }
}