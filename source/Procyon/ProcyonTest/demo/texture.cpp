
#include "pch.h"

#include <stb_image/stb_image.h>

#include "ProcyonRendering/Buffer/FElementBuffer.h"
#include "ProcyonRendering/Buffer/FVertexArray.h"
#include "ProcyonWindow/FWindow.h"
#include "ProcyonRendering/Resources/FShader.h"
#include "ProcyonRendering/Resources/Loader/FTexture2DLoader.h"

namespace Demo::Texture {
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

    TEST(ProcyonRendering, texture1) {
        InitWindow();

        // build and compile our shader zprogram
        // ------------------------------------
        const PrRendering::Resources::FShader ourShader(R"(..\..\..\asset\shader\test\TextureVS.glsl)", R"(..\..\..\asset\shader\test\TextureFS.glsl)");

        constexpr float vertices[] = {
            //   ---- 位置 ----    ---- 颜色 ----   - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // 左上
        };
        constexpr unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // load and create a texture
        // -------------------------
        unsigned int texture1, texture2;
        // texture 1
        // ---------
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load(R"(..\..\..\asset\picture\container.jpg)", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data); 
        // texture 2
        // ---------
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load(R"(..\..\..\asset\picture\awesomeface.png)", &width, &height, &nrChannels, 0);
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            //glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, width, height, 0, ((width + 3) / 4) * ((height + 3) / 4)*16, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        // -------------------------------------------------------------------------------------------
        ourShader.UseProgram(); // don't forget to activate/use the shader before setting uniforms!
        // either set it manually like so:
        glUniform1i(glGetUniformLocation(ourShader.GetID(), "texture1"), 0);
        // or set it via the texture class
        ourShader.SetInt("texture2", 1);

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // bind textures on corresponding texture units
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);

            // render container
            ourShader.UseProgram();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            app.window->SwapBuffers();
        }

    }

    TEST(ProcyonRendering, texture2) {
        InitWindow();
        const PrRendering::Resources::FShader ourShader(R"(..\..\..\asset\shader\test\TextureVS.glsl)", R"(..\..\..\asset\shader\test\TextureFS.glsl)");

        constexpr float vertices[] = {
            // positions          // colors           // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        constexpr uint32_t indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        // bind: vao->vbo->ebo
        const PrRendering::Buffer::FVertexBufferLayouts vertexBufferLayouts{
            PrRendering::Buffer::FVertexBufferLayout(0, 3, 8, false),
            PrRendering::Buffer::FVertexBufferLayout(1, 3, 8, false),
            PrRendering::Buffer::FVertexBufferLayout(2, 2, 8, false),
        };
        const PrRendering::Buffer::FVertexBuffer vbo(vertices, sizeof(vertices) / sizeof(float), vertexBufferLayouts);
        const PrRendering::Buffer::FVertexArray vao(vbo);
        PrRendering::Buffer::FElementBuffer ebo(indices, sizeof(indices) / sizeof(uint32_t));

        const auto                                             texture1 = PrRendering::Resources::Loader::FTexture2DLoader::LoadFromDisk(R"(..\..\..\asset\picture\container.jpg)");
        const auto                                             texture2 = PrRendering::Resources::Loader::FTexture2DLoader::LoadFromDisk(R"(..\..\..\asset\picture\awesomeface.png)");

        ourShader.UseProgram();
        glUniform1i(glGetUniformLocation(ourShader.GetID(), "texture1"), 0);
        ourShader.SetInt("texture2", 1);

        while (!app.window->ShouldClose()) {
            fmtlog::poll();
            app.device->PollEvents();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            texture1->Bind(0);
            texture2->Bind(1);

            ourShader.UseProgram();
            vao.Bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            app.window->SwapBuffers();
            Sleep(100);
        }
    }

}

