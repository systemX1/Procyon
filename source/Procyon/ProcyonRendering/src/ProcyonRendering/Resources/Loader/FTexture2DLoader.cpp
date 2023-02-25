

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include "ProcyonRendering/Resources/Loader/FTexture2DLoader.h"

namespace PrRendering::Resources {

    std::unique_ptr<FTexture2D> Loader::FTexture2DLoader::LoadFromDisk(const std::string& p_filePath, Settings::ETextureFilteringMode p_minFilter, Settings::ETextureFilteringMode p_magFilter, bool p_generateMipmap) {
        GLuint textureID;
        int textureWidth;
        int textureHeight;
        int channelNum;
        glGenTextures(1, &textureID);

        stbi_set_flip_vertically_on_load(true);

        if (unsigned char* dataBuffer = stbi_load(p_filePath.c_str(), &textureWidth, &textureHeight, &channelNum, 4)) {
            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(p_minFilter));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(p_magFilter));

            // See https://docs.unity.cn/cn/2022.1/Manual/class-TextureImporterOverride.html
            // Need `GL_ARB_texture_compression_s3tc` extension to support `GL_COMPRESSED_RGBA_S3TC_DXT5_EXT` and `GL_COMPRESSED_RGB_S3TC_DXT1_EXT`
            GLenum textureFormat;
            if (channelNum == 3) {
                textureFormat = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataBuffer);
                //glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, textureWidth, textureHeight, 0, ((textureWidth + 3) / 4) * ((textureHeight + 3) / 4) * 8, dataBuffer);
            } else if (channelNum == 4) {
                textureFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataBuffer);
                //glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, textureWidth, textureHeight, 0, ((textureWidth + 3) / 4) * ((textureHeight + 3) / 4) * 16, dataBuffer);
            } else {
                loge("Failed to load texture2d from {}, unsupported texture format with channelNum {}, textureID {}", p_filePath, channelNum, textureID);
            }

            if (p_generateMipmap) {
                glGenerateMipmap(GL_TEXTURE_2D);
            }

            stbi_image_free(dataBuffer);
            glBindTexture(GL_TEXTURE_2D, 0);

            logi("Load texture2d from {},w:{} h:{} channelNum:{}, textureID:{}", p_filePath, textureWidth, textureHeight, channelNum, textureID);
            return std::make_unique<FTexture2D>(textureID, p_filePath, textureWidth, textureHeight, channelNum, p_minFilter, p_magFilter, p_generateMipmap);
        } else {
            stbi_image_free(dataBuffer);
            glBindTexture(GL_TEXTURE_2D, 0);
            loge("Failed to load texture2d from {}, textureID {}", p_filePath, textureID);
            return nullptr;
        }
    }




}

