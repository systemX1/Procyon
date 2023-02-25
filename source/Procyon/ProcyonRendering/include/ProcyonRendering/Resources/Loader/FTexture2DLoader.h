#pragma once

#ifndef PRRENDERING_RESOURCES_LOADER_FTEXTURETWODLOADER_H
#define PRRENDERING_RESOURCES_LOADER_FTEXTURETWODLOADER_H

#include <memory>

#include "ProcyonRendering/Resources/FTexture2D.h"
#include "ProcyonDebug/Logger/FLogger.h"

namespace PrRendering::Resources::Loader {

    /**
    * Handle the Texture creation and destruction
    */
    class FTexture2DLoader {
    public:
        FTexture2DLoader(const FTexture2DLoader& p_other)                = delete;
        FTexture2DLoader(FTexture2DLoader&& p_other) noexcept            = delete;
        FTexture2DLoader& operator=(const FTexture2DLoader& p_other)     = delete;
        FTexture2DLoader& operator=(FTexture2DLoader&& p_other) noexcept = delete;

        FTexture2DLoader() = default;
        ~FTexture2DLoader() = default;

        /**
        * Create a texture from file
        * @param p_filePath
        * @param p_minFilter
        * @param p_magFilter
        * @param p_generateMipmap
        */
        static std::unique_ptr<FTexture2D> LoadFromDisk(const std::string& p_filePath, Settings::ETextureFilteringMode p_minFilter = Settings::ETextureFilteringMode::LinearMipmapLinear, Settings::ETextureFilteringMode p_magFilter = Settings::ETextureFilteringMode::Linear, bool p_generateMipmap = true);

        /**
        * Create a texture from a single pixel color
        * @param p_data
        * @param p_minFilter
        * @param p_magFilter
        * @param p_generateMipmap
        */
        //static std::unique_ptr<FTexture2D> LoadColor(uint32_t p_data, Settings::ETextureFilteringMode p_minFilter = Settings::ETextureFilteringMode::Linear, Settings::ETextureFilteringMode p_magFilter = Settings::ETextureFilteringMode::Linear, bool p_generateMipmap = true);

        /**
        * Create a texture from memory
        * @param p_data
        * @param p_width
        * @param p_height
        * @param p_minFilter
        * @param p_magFilter
        * @param p_generateMipmap
        */
        //static std::unique_ptr<FTexture2D> LoadFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height, Settings::ETextureFilteringMode p_minFilter = Settings::ETextureFilteringMode::Linear, Settings::ETextureFilteringMode p_magFilter = Settings::ETextureFilteringMode::Linear, bool p_generateMipmap = true);

        /**
        * Reload a texture from file
        * @param p_texture
        * @param p_filePath
        * @param p_minFilter
        * @param p_magFilter
        * @param p_generateMipmap
        */
        //static void Reload(FTexture2D& p_texture, const std::string& p_filePath, Settings::ETextureFilteringMode p_minFilter = Settings::ETextureFilteringMode::Linear, Settings::ETextureFilteringMode p_magFilter = Settings::ETextureFilteringMode::Linear, bool p_generateMipmap = true);
    };

}

#endif
