
#include "ProcyonWindow/Device/FDevice.h"


PrWindow::Device::FDevice::FDevice(const Settings::FDeviceSettings& p_deviceSettings) {
    BindErrorCallback();
    if(const int initCode = glfwInit(); initCode == GLFW_FALSE) {
        glfwTerminate();

        assert(initCode == GLFW_TRUE && "glfwInit failed");
    } 

    CreateCursors();

    if (p_deviceSettings.isDebugProfile)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_deviceSettings.contextMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_deviceSettings.contextMinorVersion);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, p_deviceSettings.samples);

    m_isAlive = true;
}

PrWindow::Device::FDevice::~FDevice()
{
    if (m_isAlive) {
        DestroyCursors();
        glfwTerminate();
    }
}

GLFWcursor* PrWindow::Device::FDevice::GetCursorInstance(Cursor::ECursorShape p_cursorShape) const
{
    return nullptr;
}

bool PrWindow::Device::FDevice::HasVsync() const {
    return m_isVsync;
}

void PrWindow::Device::FDevice::SetVsync(const bool p_value) {
    glfwSwapInterval(p_value ? 1 : 0);
    m_isVsync = p_value;
}

void PrWindow::Device::FDevice::PollEvents() const {
    glfwPollEvents();
}

float PrWindow::Device::FDevice::GetElapsedTime() const {
    return static_cast<float>(glfwGetTime());
}

void PrWindow::Device::FDevice::BindErrorCallback()
{
    auto errorCallback = [](const int p_code, const char* p_description){
        printf("%d %s\n", p_code, p_description);
        //ErrorEvent.Invoke(static_cast<EDeviceError>(p_code), p_description);
    };

    glfwSetErrorCallback(errorCallback);
}

void PrWindow::Device::FDevice::CreateCursors() {
    m_cursors[Cursor::ECursorShape::Arrow] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::Arrow));
    m_cursors[Cursor::ECursorShape::IBeam] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::IBeam));
    m_cursors[Cursor::ECursorShape::Corsshair] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::Corsshair));
    m_cursors[Cursor::ECursorShape::Hand] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::Hand));
    m_cursors[Cursor::ECursorShape::HResize] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::HResize));
    m_cursors[Cursor::ECursorShape::VResize] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::VResize));
}

void PrWindow::Device::FDevice::DestroyCursors() {
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::Arrow]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::IBeam]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::Corsshair]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::Hand]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::HResize]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::VResize]);
}
