#pragma once

#ifndef PREDITOR_CORE_FCONTEXT_H
#define PREDITOR_CORE_FCONTEXT_H

#include <memory>

#include "ProcyonWindow/FWindow.h"
#include "ProcyonWindow/Device/FDevice.h"
#include "ProcyonWindow/Settings/FWindowSettings.h"
#include "ProcyonWindow/Settings/FDeviceSettings.h"


namespace PrEditor::Core {
    class FContext {
    public:
        FContext(const FContext& p_other)     = delete;
        FContext(FContext&& p_other) noexcept = delete;
        FContext& operator=(FContext p_other) = delete;

        FContext(const std::string& p_projectPath, const std::string& p_projectName);

        ~FContext();

        std::unique_ptr<PrWindow::FWindow>                  window;
        std::unique_ptr<PrWindow::Device::FDevice>          device;

        PrWindow::Settings::FWindowSettings         windowSettings;

    };

}

#endif

