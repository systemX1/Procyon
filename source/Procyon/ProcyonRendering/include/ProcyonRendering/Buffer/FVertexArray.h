#pragma once

#ifndef PRRENDERING_BUFFER_FVERTEXARRAY_H
#define PRRENDERING_BUFFER_FVERTEXARRAY_H

#include "TVertexBuffer.h"

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
        /**
        * Create the vertex array
        */
        explicit FVertexArray();

        /**
        * Destroy the vertex array
        */
        ~FVertexArray();

        /**
        * Register a VBO into the VAO
        * @param p_vertexAttributeIndex
        * @param p_vertexBuffer
        * @param p_type
        * @param p_count
        * @param p_stride
        * @param p_offset
        */
        template <class T>
        void BindAttribute(TVertexBuffer<T>& p_vertexBuffer, uint32_t p_vertexAttributeIndex, uint64_t p_size, EType p_type, uint64_t p_stride, intptr_t p_offset);

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
        uint32_t m_bufferID;
    };

}

#include "FVertexArray.inl"

#endif
