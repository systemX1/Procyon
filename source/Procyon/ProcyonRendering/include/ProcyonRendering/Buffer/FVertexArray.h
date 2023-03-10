#pragma once

#ifndef PRRENDERING_BUFFER_FVERTEXARRAY_H
#define PRRENDERING_BUFFER_FVERTEXARRAY_H

#include "FVertexBuffer.h"

namespace PrRendering::Buffer {

    /**
    * Wraps from OpenGL types enum
    */
    enum class EType : int
    {
        Byte = GL_BYTE,
        UnisgnedByte = GL_UNSIGNED_BYTE,
        Short = GL_SHORT,
        UnsignedShort = GL_UNSIGNED_SHORT,
        Int = GL_INT,
        UnsignedInt = GL_UNSIGNED_INT,
        Float = GL_FLOAT,
        Double = GL_DOUBLE
    };

    /**
    * Wraps OpenGL VAO
    */
    class FVertexArray {
    public:
        FVertexArray(const FVertexArray& p_other)                = delete;
        FVertexArray(FVertexArray&& p_other) noexcept            = delete;
        FVertexArray& operator=(const FVertexArray& p_other)     = delete;
        FVertexArray& operator=(FVertexArray&& p_other) noexcept = delete;

        /**
        * Create the vertex array
        */
        explicit FVertexArray();

        explicit FVertexArray(const std::vector<FVertexBuffer>& p_vertexBuffers);

        explicit FVertexArray(const FVertexBuffer& p_vertexBuffer);

        /**
        * Destroy the vertex array
        */
        ~FVertexArray();

        /**
        * Register a VBO into the VAO
        * @param p_vertexAttributeIndex
        * @param p_vertexBuffer
        * @param p_type
        * @param p_size
        * @param p_stride
        * @param p_offset
        */
        void BindAttribute(const FVertexBuffer& p_vertexBuffer, uint32_t p_vertexAttributeIndex, uint64_t p_size, EType p_type, uint64_t p_stride, intptr_t p_offset);

        /**
        * Bind the buffer
        */
        void Bind() const;

        /**
        * Unbind the buffer
        */
        static void Unbind();

        /**
        * Return the VAO OpenGL ID
        */
        [[nodiscard]] uint32_t GetID() const;

    private:
        uint32_t m_bufferID = 0;
    };

}

#include "FVertexArray.inl"

#endif
