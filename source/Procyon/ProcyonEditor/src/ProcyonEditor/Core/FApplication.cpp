
#include "ProcyonEditor/Core/FApplication.h"

PrEditor::Core::FApplication::FApplication(const std::string& p_projectPath, const std::string& p_projectName) :
    m_context("", ""), m_editor(m_context) {
}

void PrEditor::Core::FApplication::Run() {
    PrUtil::Time::FClock clock;

    while (IsRunning()) {
        m_editor.PreUpdate();
        m_editor.Update(clock.GetDeltaTime());
        m_editor.PostUpdate();

        clock.Update();
    }
}

bool PrEditor::Core::FApplication::IsRunning() const {
    return !m_context.window->ShouldClose();
}



