#pragma once

#ifndef PRRENDERING_BUFFER_FELEMENTBUFFER_H
#define PRRENDERING_BUFFER_FELEMENTBUFFER_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace PrRendering::Buffer {


    /**
    * Wraps OpenGL EBO
    */
    class FElementBuffer {
    public:
        FElementBuffer(const FElementBuffer& p_other)                = delete;
        FElementBuffer(FElementBuffer&& p_other) noexcept            = delete;
        FElementBuffer& operator=(const FElementBuffer& p_other)     = delete;
        FElementBuffer& operator=(FElementBuffer&& p_other) noexcept = delete;

        /**
        * Create the EBO using a pointer to the first element and a size (number of elements)
        * @param p_data
        * @parma p_dataSize
        */
        FElementBuffer(const uint32_t* p_data, size_t p_dataSize);

        /**
        * Create the EBO using a vector
        * @param p_data
        */
        explicit FElementBuffer(const std::vector<uint32_t>& p_data);

        /**
        * Destructor
        */
        ~FElementBuffer();

        /**
        * Bind the buffer
        */
        void Bind() const;

        /**
        * Unbind the buffer
        */
        void Unbind();

        /**
        * Returns the ID of the OpenGL EBO
        */
        [[nodiscard]] uint32_t GetID() const;

    private:
        uint32_t m_bufferID;
    };

}

#include "FElementBuffer.inl"

#endif
