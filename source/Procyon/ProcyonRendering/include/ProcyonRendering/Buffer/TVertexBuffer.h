#pragma once

#ifndef PRRENDERING_BUFFER_TVERTEXBUFFER_H
#define PRRENDERING_BUFFER_TVERTEXBUFFER_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ProcyonDebug/Logger/FLogger.h"

namespace PrRendering::Buffer {

    /**
    * Wraps OpenGL VBO
    */
    template <class T>
    class TVertexBuffer {
    public:
        /**
        * Create the VBO using a pointer to the first element and a size (number of elements)
        * @param p_data
        * @param p_dataSize
        */
        TVertexBuffer(const T* p_data, const size_t p_dataSize);

        /**
        * Create the EBO using a vector
        * @param p_data
        */
        explicit TVertexBuffer(std::vector<T>& p_data);

        /**
        * Destructor
        */
        ~TVertexBuffer();

        /**
        * Bind the buffer
        */
        void Bind() const;

        /**
        * Bind the buffer
        */
        void Unbind();

        /**
        * Returnd the ID of the VBO
        */
        [[nodiscard]] uint32_t GetID() const;

    private:
        uint32_t m_bufferID;
    };

}

#include "TVertexBuffer.inl"

#endif


