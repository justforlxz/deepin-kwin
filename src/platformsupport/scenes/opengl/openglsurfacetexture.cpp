/*
    SPDX-FileCopyrightText: 2021 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openglsurfacetexture.h"
#include "deepin_kwingltexture.h"

namespace KWin
{

OpenGLSurfaceTexture::OpenGLSurfaceTexture(OpenGLBackend *backend)
    : m_backend(backend)
{
}

OpenGLSurfaceTexture::~OpenGLSurfaceTexture()
{
}

bool OpenGLSurfaceTexture::isValid() const
{
    return m_texture;
}

OpenGLBackend *OpenGLSurfaceTexture::backend() const
{
    return m_backend;
}

GLTexture *OpenGLSurfaceTexture::texture() const
{
    return m_texture.data();
}

} // namespace KWin
