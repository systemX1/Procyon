
#include "ProcyonEditor/Core/FContext.h"



PrEditor::Core::FContext::FContext(const std::string& p_projectPath, const std::string& p_projectName) {

    // Settings
    PrWindow::Settings::FDeviceSettings deviceSettings;
    deviceSettings.contextMajorVersion = 4;
    deviceSettings.contextMinorVersion = 6;
    windowSettings.title = "Procyon Editor";
    windowSettings.width = 1280;
    windowSettings.height = 720;
    windowSettings.isMaximized = true;
    windowSettings.isFullscreen = false;

    // Window creation
    device = std::make_unique<PrWindow::Device::FDevice>(deviceSettings);
    window = std::make_unique<PrWindow::FWindow>(*device, windowSettings);

    window->MakeCurrentContext();

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        assert(false && "gladLoadGLLoader failed");
    }
}

PrEditor::Core::FContext::~FContext() {

}

