#pragma once

#ifndef PRRENDERING_SETTINGS_ETEXTUREFILTERINGMODE_H
#define PRRENDERING_SETTINGS_ETEXTUREFILTERINGMODE_H

#include <glad/glad.h>

namespace PrRendering::Settings {

    /**
    * OpenGL texture filtering mode enum wrapper
    */
    enum class ETextureFilteringMode
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
        NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
        LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
        LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
        NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR
    };

}

#endif
