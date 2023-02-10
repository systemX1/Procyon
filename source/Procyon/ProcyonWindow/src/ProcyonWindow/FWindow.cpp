#include "ProcyonWindow/FWindow.h"

// 类的静态成员变量需要在类定义外分配空间
std::unordered_map<GLFWwindow*, PrWindow::FWindow*> PrWindow::FWindow::m_windowMap;

PrWindow::FWindow::FWindow(const Device::FDevice& p_device, const Settings::FWindowSettings& p_windowSettings) :
    m_device(p_device),
    m_title(p_windowSettings.title),
    m_size{ p_windowSettings.width, p_windowSettings.height },
    m_minimumSize{ p_windowSettings.minimumWidth, p_windowSettings.minimumHeight },
    m_maximumSize{ p_windowSettings.maximumWidth, p_windowSettings.maximumHeight },
    m_fullscreen(p_windowSettings.fullscreen),
    m_refreshRate(p_windowSettings.refreshRate)
{
	/* Window creation */
	CreateGlfwWindow(p_windowSettings);

	/* Window settings */
	SetCursorMode(p_windowSettings.cursorMode);
	SetCursorShape(p_windowSettings.cursorShape);

	/* Callback binding */
	BindKeyCallback();
	BindMouseCallback();
	BindIconifyCallback();
	BindCloseCallback();
	BindResizeCallback();
	BindCursorMoveCallback();
	BindFramebufferResizeCallback();
	BindMoveCallback();
	BindFocusCallback();



}

void PrWindow::FWindow::CreateGlfwWindow(const Settings::FWindowSettings& p_windowSettings) {
    GLFWmonitor* selectedMonitor = nullptr;

    if (m_fullscreen)
        selectedMonitor = glfwGetPrimaryMonitor();

    glfwWindowHint(GLFW_RESIZABLE, p_windowSettings.resizable);
    glfwWindowHint(GLFW_DECORATED, p_windowSettings.decorated);
    glfwWindowHint(GLFW_FOCUSED, p_windowSettings.focused);
    glfwWindowHint(GLFW_MAXIMIZED, p_windowSettings.maximized);
    glfwWindowHint(GLFW_FLOATING, p_windowSettings.floating);
    glfwWindowHint(GLFW_VISIBLE, p_windowSettings.visible);
    glfwWindowHint(GLFW_AUTO_ICONIFY, p_windowSettings.autoIconify);
    glfwWindowHint(GLFW_REFRESH_RATE, p_windowSettings.refreshRate);
    glfwWindowHint(GLFW_SAMPLES, p_windowSettings.samples);

    //m_glfwWindow = glfwCreateWindow(m_size.first, m_size.second, m_title.c_str(), selectedMonitor, nullptr);
    m_glfwWindow = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

    assert(m_glfwWindow != nullptr && "create GLFW window failed");
    
    //UpdateSizeLimit();

    auto [x, y] = GetPosition();
    m_position.first = x;
    m_position.second = y;

    m_windowMap[m_glfwWindow] = this;
}

PrWindow::FWindow* PrWindow::FWindow::GetFWindowInstance(GLFWwindow* p_glfwWindow)
{
	return m_windowMap.contains(p_glfwWindow)
            ? m_windowMap[p_glfwWindow]
            : nullptr;
}

void PrWindow::FWindow::SetIcon(const std::string& p_filePath)
{
}

void PrWindow::FWindow::SetIconFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height)
{
}

void PrWindow::FWindow::SetSize(uint16_t p_width, uint16_t p_height)
{
}

void PrWindow::FWindow::SetMinimumSize(int16_t p_minimumWidth, int16_t p_minimumHeight) {}
void PrWindow::FWindow::SetMaximumSize(int16_t p_maximumWidth, int16_t p_maximumHeight) {}
void PrWindow::FWindow::SetPosition(int16_t p_x, int16_t p_y) {}
void PrWindow::FWindow::Minimize() const {}
void PrWindow::FWindow::Maximize() const {}
void PrWindow::FWindow::Restore() const {}
void PrWindow::FWindow::Hide() const {}
void PrWindow::FWindow::Show() const {}
void PrWindow::FWindow::Focus() const {}
void PrWindow::FWindow::SetShouldClose(bool p_value) const {}

bool PrWindow::FWindow::ShouldClose() const {
    return glfwWindowShouldClose(m_glfwWindow);
}

void PrWindow::FWindow::SetFullscreen(bool p_value) {}
void PrWindow::FWindow::ToggleFullscreen() {}

bool PrWindow::FWindow::IsFullscreen() const {
    return false;
}

bool PrWindow::FWindow::IsHidden() const {
    return false;
}

bool PrWindow::FWindow::IsVisible() const {
    return false;
}

bool PrWindow::FWindow::IsMaximized() const {
    return false;
}

bool PrWindow::FWindow::IsMinimized() const {
    return false;
}

bool PrWindow::FWindow::IsFocused() const {
    return false;
}

bool PrWindow::FWindow::IsResizable() const {
    return false;
}

bool PrWindow::FWindow::IsDecorated() const {
    return false;
}

void PrWindow::FWindow::MakeCurrentContext() const {
    glfwMakeContextCurrent(m_glfwWindow);
}

void PrWindow::FWindow::SwapBuffers() const {
    glfwSwapBuffers(m_glfwWindow);

}

void PrWindow::FWindow::SetCursorMode(Cursor::ECursorMode p_cursorMode) {}
void PrWindow::FWindow::SetCursorShape(Cursor::ECursorShape p_cursorShape) {}
void PrWindow::FWindow::SetCursorPosition(int16_t p_x, int16_t p_y) {}
void PrWindow::FWindow::SetTitle(const std::string& p_title) {}
void PrWindow::FWindow::SetRefreshRate(int32_t p_refreshRate) {}

std::string PrWindow::FWindow::GetTitle() const {
    return {};
}

std::pair<uint16_t, uint16_t> PrWindow::FWindow::GetSize() const {
    return {};
}

std::pair<int16_t, int16_t> PrWindow::FWindow::GetMinimumSize() const {
    return {};
}

std::pair<int16_t, int16_t> PrWindow::FWindow::GetMaximumSize() const {
    return {};
}

std::pair<uint16_t, uint16_t> PrWindow::FWindow::GetFramebufferSize() const {
    return {};
}

PrWindow::Cursor::ECursorMode PrWindow::FWindow::GetCursorMode() const {
    return m_cursorMode;
}

PrWindow::Cursor::ECursorShape PrWindow::FWindow::GetCursorShape() const {
    return m_cursorShape;
}

int32_t PrWindow::FWindow::GetRefreshRate() const {
    return 0;
}

GLFWwindow* PrWindow::FWindow::GetGlfwWindow() const {
    return nullptr;
}

std::pair<int16_t, int16_t> PrWindow::FWindow::GetPosition() const {
	int x, y;
	glfwGetWindowPos(m_glfwWindow, &x, &y);
	return std::make_pair(static_cast<int16_t>(x), static_cast<int16_t>(y));
}


PrWindow::FWindow::~FWindow()
{
	glfwDestroyWindow(m_glfwWindow);
}

void PrWindow::FWindow::BindKeyCallback() const {
	auto keyCallback = [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods) {
        if (FWindow* windowInstance = GetFWindowInstance(p_window)) {
			//if (p_action == GLFW_PRESS)
				//windowInstance->KeyPressedEvent.Invoke(p_key);

			//if (p_action == GLFW_RELEASE)
				//windowInstance->KeyReleasedEvent.Invoke(p_key);
		}
	};

	glfwSetKeyCallback(m_glfwWindow, keyCallback);
}

void PrWindow::FWindow::BindMouseCallback() const {
}

void PrWindow::FWindow::BindResizeCallback() const {
}

void PrWindow::FWindow::BindFramebufferResizeCallback() const {
    auto framebufferResizeCallback = [](GLFWwindow* p_window, int p_width, int p_height) {
        FWindow* windowInstance = GetFWindowInstance(p_window);
        glViewport(0, 0, windowInstance->m_size.first, windowInstance->m_size.second);

        /*
        if (windowInstance) {
            windowInstance->FramebufferResizeEvent.Invoke(static_cast<uint16_t>(p_width), static_cast<uint16_t>(p_height));
        }*/
    };

    glfwSetFramebufferSizeCallback(m_glfwWindow, framebufferResizeCallback);
}

void PrWindow::FWindow::BindCursorMoveCallback() const {
}

void PrWindow::FWindow::BindMoveCallback() const {
}

void PrWindow::FWindow::BindIconifyCallback() const {
}

void PrWindow::FWindow::BindFocusCallback() const {
}

void PrWindow::FWindow::BindCloseCallback() const {
}
