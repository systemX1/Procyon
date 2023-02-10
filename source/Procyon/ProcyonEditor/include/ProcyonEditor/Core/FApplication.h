#pragma once

#ifndef PREDITOR_CORE_FAPPLICATION_H
#define PREDITOR_CORE_FAPPLICATION_H

#include <utility>


#include "ProcyonEditor/Core/FContext.h"
#include "ProcyonEditor/Core/FEditor.h"
#include "ProcyonTool/Time/FClock.h"

namespace PrEditor::Core {
	
	// Entry point of OvEditor
	class FApplication
	{
    public:
        FApplication(const FApplication& p_other)                = default;
        FApplication(FApplication&& p_other) noexcept            = default;
        FApplication& operator=(const FApplication& p_other)     = default;
        FApplication& operator=(FApplication&& p_other) noexcept = default;

	    FApplication(const std::string& p_projectPath, const std::string& p_projectName);

		~FApplication() = default;

		void Run();

		[[nodiscard]] bool IsRunning() const;
		
	private:
		FContext m_context;
		FEditor  m_editor;
	};

} 

#endif

