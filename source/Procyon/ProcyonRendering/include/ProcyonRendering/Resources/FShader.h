#pragma once

#ifndef PRRENDERING_RESOURCES_FSHADER_H
#define PRRENDERING_RESOURCES_FSHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <cassert>

#include "ProcyonDebug/Logger/FLogger.h"

namespace PrRendering::Resources {

	class FShader
	{
    public:
        FShader(const char* p_vertexShaderPath, const char* p_fragmentShaderPath);
        void                   UseProgram() const;
        void                   UnUseProgram() const;
        void                   SetBool(const std::string& p_name, bool p_value) const;
        void                   SetInt(const std::string& p_name, int p_value) const;
        void                   SetFloat(const std::string& p_name, float p_value) const;
        [[nodiscard]] uint32_t GetID() const;

        // TODO: Uniform


    private:
        uint32_t m_id;
    
        // utility function for checking shader compilation/linking errors.
        static void CheckCompileErrors(unsigned int p_shader, const std::string& p_type);
	};


};

#endif
