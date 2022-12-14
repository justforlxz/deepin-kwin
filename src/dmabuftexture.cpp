/*
    SPDX-FileCopyrightText: 2020 Aleix Pol Gonzalez <aleixpol@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dmabuftexture.h"

#include "kwineglimagetexture.h"
#include "deepin_kwinglutils.h"

namespace KWin
{

DmaBufTexture::DmaBufTexture(KWin::GLTexture *texture)
    : m_texture(texture)
    , m_framebuffer(new KWin::GLRenderTarget(*m_texture))
{
}

DmaBufTexture::~DmaBufTexture() = default;

KWin::GLTexture *DmaBufTexture::texture() const
{
    return m_texture.data();
}

KWin::GLRenderTarget *DmaBufTexture::framebuffer() const
{
    return m_framebuffer.data();
}

} // namespace KWin
