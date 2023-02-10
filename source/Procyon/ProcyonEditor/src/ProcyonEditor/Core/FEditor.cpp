#include "ProcyonEditor/Core/FEditor.h"

PrEditor::Core::FEditor::FEditor(FContext& p_context) :
    m_context(p_context) {

    SetupUI();

}

PrEditor::Core::FEditor::~FEditor() {
}

void PrEditor::Core::FEditor::SetupUI() {
}

void PrEditor::Core::FEditor::PreUpdate() {
    m_context.device->PollEvents();


}

void PrEditor::Core::FEditor::Update(float p_deltaTime) {
}

void PrEditor::Core::FEditor::PostUpdate() {
    m_context.window->SwapBuffers();
    ++m_elapsedFrames;
}

void PrEditor::Core::FEditor::HandleGlobalShortcuts()
{
}

void PrEditor::Core::FEditor::UpdateCurrentEditorMode(float p_deltaTime)
{
}

void PrEditor::Core::FEditor::UpdatePlayMode(float p_deltaTime)
{
}

void PrEditor::Core::FEditor::UpdateEditMode(float p_deltaTime)
{
}

void PrEditor::Core::FEditor::UpdateEditorPanels(float p_deltaTime)
{
}

void PrEditor::Core::FEditor::PrepareRendering(float p_deltaTime)
{
}

void PrEditor::Core::FEditor::RenderViews(float p_deltaTime)
{
}

void PrEditor::Core::FEditor::RenderEditorUI(float p_deltaTime)
{
}

