
#include "ProcyonRendering/Resources/FTexture2D.h"

void PrRendering::Resources::FTexture2D::Bind(const uint32_t p_slot) const {
    glActiveTexture(GL_TEXTURE0 + p_slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}
void PrRendering::Resources::FTexture2D::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

PrRendering::Resources::FTexture2D::FTexture2D(
    const uint32_t p_id,
    std::string p_path, 
    const uint32_t p_width, 
    const uint32_t p_height, 
    const uint32_t p_bitsPerPixel, 
    const Settings::ETextureFilteringMode p_minFilter, 
    const Settings::ETextureFilteringMode p_magFilter, 
    const bool p_generateMipmap) :
    m_id(p_id),
    m_path(std::move(p_path)),
    m_isMimapped(p_generateMipmap),
    m_width(p_width),
    m_height(p_height),
    m_bitsPerPixel(p_bitsPerPixel),
    m_minFilter(p_minFilter),
    m_magFilter(p_magFilter) {}

PrRendering::Resources::FTexture2D::~FTexture2D() {
    glDeleteTextures(1, &m_id);
}

