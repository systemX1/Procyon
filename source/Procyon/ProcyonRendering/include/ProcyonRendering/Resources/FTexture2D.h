#pragma once

#ifndef PRRENDERING_RESOURCES_FTEXTURE_H
#define PRRENDERING_RESOURCES_FTEXTURE_H

#include <cstdint>
#include <string>

#include "ProcyonRendering/Settings/ETextureFilteringMode.h"

namespace PrRendering::Resources {
    namespace Loader {
        class FTexture2DLoader;
    }

    /**
    * OpenGL texture wrapper
    */
    class FTexture2D {
        friend class Loader::FTexture2DLoader;

    public:
        FTexture2D(const FTexture2D& p_other)                = delete;
        FTexture2D(FTexture2D&& p_other) noexcept            = delete;
        FTexture2D& operator=(const FTexture2D& p_other)     = delete;
        FTexture2D& operator=(FTexture2D&& p_other) noexcept = delete;

        /**
		* Bind the texture to the given slot
		* @param p_slot
		*/
		void Bind(uint32_t p_slot) const;

		/**
		* Unbind the texture
		*/
		void Unbind() const;

		FTexture2D(uint32_t p_id, std::string p_path, uint32_t p_width, uint32_t p_height, uint32_t p_bitsPerPixel, Settings::ETextureFilteringMode p_minFilter, Settings::ETextureFilteringMode p_magFilter, bool p_generateMipmap);

		~FTexture2D();

    private:
        const uint32_t                        m_id;
        const std::string                     m_path;
        const bool                            m_isMimapped;
        const uint32_t                        m_width;
		const uint32_t                        m_height;
		const uint32_t                        m_bitsPerPixel;
		const Settings::ETextureFilteringMode m_minFilter;
		const Settings::ETextureFilteringMode m_magFilter;
	};

}

#endif
