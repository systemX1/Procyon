#pragma once

#ifndef PRRENDERING_BUFFER_FVERTEXARRAY_INL
#define PRRENDERING_BUFFER_FVERTEXARRAY_INL

#include "FVertexArray.h"

namespace PrRendering::Buffer {
    inline FVertexArray::FVertexArray() : m_bufferID(0) {
        glGenVertexArrays(1, &m_bufferID);
        glBindVertexArray(m_bufferID);
        logd("gen and bind FVertexArray {}", m_bufferID);
    }

    inline FVertexArray::~FVertexArray() {
        glDeleteVertexArrays(1, &m_bufferID);
        logd("del FVertexArray {}", m_bufferID);
    }

    template<class T>
    void FVertexArray::BindAttribute(TVertexBuffer<T>& p_vertexBuffer, const uint32_t p_vertexAttributeIndex, const uint64_t p_size, EType p_type, const uint64_t p_stride, const intptr_t p_offset) {
        Bind();
        p_vertexBuffer.Bind();
        glEnableVertexAttribArray(p_vertexAttributeIndex);
        glVertexAttribPointer(static_cast<GLuint>(p_vertexAttributeIndex), static_cast<GLint>(p_size), static_cast<GLenum>(p_type), GL_FALSE, static_cast<GLsizei>(p_stride), reinterpret_cast<const GLvoid*>(p_offset));
        logd("BindAttribute FVertexArray {}", m_bufferID);
    }

    inline void FVertexArray::Bind() const {
        glBindVertexArray(m_bufferID);
    }

    inline void FVertexArray::Unbind() {
        glBindVertexArray(0);
    }

    inline uint32_t FVertexArray::GetID() const {
        return m_bufferID;
    }

}



#endif



