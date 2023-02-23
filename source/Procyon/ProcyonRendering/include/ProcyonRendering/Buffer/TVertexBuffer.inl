#pragma once

#ifndef PRRENDERING_BUFFER_TVERTEXBUFFER_INL
#define PRRENDERING_BUFFER_TVERTEXBUFFER_INL

#include "TVertexBuffer.h"

namespace PrRendering::Buffer {
    template<class T>
    TVertexBuffer<T>::TVertexBuffer(const T* p_data, const size_t p_dataSize) {
        glGenBuffers(1, &m_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ARRAY_BUFFER, p_dataSize * sizeof(T), p_data, GL_STATIC_DRAW);
        logd("gen, bind and glBufferData TVertexBuffer {}", m_bufferID);
    }

    template<class T>
    TVertexBuffer<T>::TVertexBuffer(std::vector<T>& p_data) : TVertexBuffer(p_data.data(), p_data.size()) {
    }

    template<class T>
    TVertexBuffer<T>::~TVertexBuffer() {
        glDeleteBuffers(1, &m_bufferID);
        logd("del TVertexBuffer {}", m_bufferID);
    }

    template<class T>
    void TVertexBuffer<T>::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        logd("bind TVertexBuffer {}", m_bufferID);
    }

    template<class T>
    void TVertexBuffer<T>::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        logd("unbind TVertexBuffer");
    }

    template<class T>
    uint32_t TVertexBuffer<T>::GetID() const {
        return m_bufferID;
    }

}

#endif

