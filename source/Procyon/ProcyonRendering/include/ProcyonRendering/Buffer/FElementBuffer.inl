#pragma once

#ifndef PRRENDERING_BUFFER_FELEMENTBUFFER_INL
#define PRRENDERING_BUFFER_FELEMENTBUFFER_INL

#include "FElementBuffer.h"

namespace PrRendering::Buffer {

    inline FElementBuffer::FElementBuffer(const uint32_t* p_data, const size_t p_dataSize) :m_bufferID{0} {
        glGenBuffers(1, &m_bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(p_dataSize) * sizeof(uint32_t), p_data, GL_STATIC_DRAW);
    }

    inline FElementBuffer::FElementBuffer(const std::vector<uint32_t>& p_data) : FElementBuffer(p_data.data(), p_data.size()) {
    }

    inline FElementBuffer::~FElementBuffer()
    {
        glDeleteBuffers(1, &m_bufferID);
    }

    inline void FElementBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    }

    inline void FElementBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    inline uint32_t FElementBuffer::GetID() const {
        return m_bufferID;
    }

}


#endif

