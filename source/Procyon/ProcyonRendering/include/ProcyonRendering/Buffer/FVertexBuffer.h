#pragma once

#ifndef PRRENDERING_BUFFER_TVERTEXBUFFER_H
#define PRRENDERING_BUFFER_TVERTEXBUFFER_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ProcyonDebug/Logger/FLogger.h"

namespace PrRendering::Buffer {

    struct FVertexBufferLayout {
        int location;
        int size;
        uint64_t stride;
        bool isNormalized;

        FVertexBufferLayout(const int p_location, const int p_size, const uint64_t p_stride, const bool p_isNormalized) :
            location{p_location},
            size{p_size},
            stride{p_stride},
            isNormalized{p_isNormalized} {}
    };

    using FVertexBufferLayouts = std::vector<FVertexBufferLayout>;

    /**
    * Wraps OpenGL VBO
    */
    class FVertexBuffer {
    public:
        FVertexBuffer(const FVertexBuffer& p_other)                = delete;
        FVertexBuffer(FVertexBuffer&& p_other) noexcept            = delete;
        FVertexBuffer& operator=(const FVertexBuffer& p_other)     = delete;
        FVertexBuffer& operator=(FVertexBuffer&& p_other) noexcept = delete;

        /**
        * Create the VBO using a pointer to the first element and a size (number of elements)
        * @param p_data
        * @param p_dataSize
        */
        FVertexBuffer(const float* p_data, const size_t p_dataSize);

        /**
        * Create the EBO using a vector
        * @param p_data
        */
        explicit FVertexBuffer(const std::vector<float>& p_data);

        /**
        * Create the VBO using a pointer to the first element and a size (number of elements)
        * @param p_data
        * @param p_dataSize
        * @param p_vertexBufferLayouts
        */
        FVertexBuffer(const float* p_data, const size_t p_dataSize, const FVertexBufferLayouts& p_vertexBufferLayouts);

        /**
        * Create the EBO using a vector
        * @param p_data
        * @param p_vertexBufferLayouts
        */
        FVertexBuffer(const std::vector<float>& p_data, const FVertexBufferLayouts& p_vertexBufferLayouts);

        /**
        * Destructor
        */
        ~FVertexBuffer();

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

        void AddVertexBufferLayout(const FVertexBufferLayouts& p_vertexBufferLayouts);

    public:
        FVertexBufferLayouts vertexBufferLayouts;

    private:
        uint32_t m_bufferID;
    };

}

#include "FVertexBuffer.inl"

#endif


