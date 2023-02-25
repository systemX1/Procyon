#pragma once

#ifndef PRRENDERING_BUFFER_TVERTEXBUFFER_INL
#define PRRENDERING_BUFFER_TVERTEXBUFFER_INL

#include "FElementBuffer.h"
#include "FVertexBuffer.h"

namespace PrRendering::Buffer {

    inline FVertexBuffer::FVertexBuffer(const float* p_data, const size_t p_dataSize) : vertexBufferLayouts{}, m_bufferID{0} {
        glGenBuffers(1, &m_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ARRAY_BUFFER, static_cast<int64_t>(p_dataSize) * sizeof(float), p_data, GL_STATIC_DRAW);
        logd("gen, bind and glBufferData FVertexBuffer {}", m_bufferID);
    }

    inline FVertexBuffer::FVertexBuffer(const std::vector<float>& p_data) : FVertexBuffer(p_data.data(), p_data.size()) {
    }

    inline FVertexBuffer::FVertexBuffer(const float* p_data, const size_t p_dataSize,
        const FVertexBufferLayouts& p_vertexBufferLayouts)
            : FVertexBuffer(p_data, p_dataSize) {
        AddVertexBufferLayout(p_vertexBufferLayouts);
    }

    inline FVertexBuffer::FVertexBuffer(const std::vector<float>& p_data,
        const FVertexBufferLayouts& p_vertexBufferLayouts) : FVertexBuffer(p_data.data(), p_data.size()) {
        AddVertexBufferLayout(p_vertexBufferLayouts);
    }

    inline FVertexBuffer::~FVertexBuffer() {
        glDeleteBuffers(1, &m_bufferID);
        logd("del FVertexBuffer {}", m_bufferID);
    }

    inline void FVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
    }

    inline void FVertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    inline uint32_t FVertexBuffer::GetID() const {
        return m_bufferID;
    }

    inline void FVertexBuffer::AddVertexBufferLayout(const FVertexBufferLayouts& p_vertexBufferLayouts)
    {
        for (const auto& layout : p_vertexBufferLayouts) {
            vertexBufferLayouts.emplace_back(layout);
        }
    }

}

#endif

