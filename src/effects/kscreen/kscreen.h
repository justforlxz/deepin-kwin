/*
    KWin - the KDE window manager
    This file is part of the KDE project.

    SPDX-FileCopyrightText: 2013 Martin Gräßlin <mgraesslin@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef KWIN_KSCREEN_H
#define KWIN_KSCREEN_H

#include <deepin_kwineffects.h>

namespace KWin
{

class KscreenEffect : public Effect
{
    Q_OBJECT

public:
    KscreenEffect();
    ~KscreenEffect() override;

    void prePaintScreen(ScreenPrePaintData &data, std::chrono::milliseconds presentTime) override;
    void postPaintScreen() override;
    void prePaintWindow(EffectWindow *w, WindowPrePaintData &data, std::chrono::milliseconds presentTime) override;
    void paintWindow(EffectWindow *w, int mask, QRegion region, WindowPaintData &data) override;

    void reconfigure(ReconfigureFlags flags) override;
    bool isActive() const override;

    int requestedEffectChainPosition() const override {
        return 99;
    }

private Q_SLOTS:
    void propertyNotify(KWin::EffectWindow *window, long atom);

private:
    enum FadeOutState {
        StateNormal,
        StateFadingOut,
        StateFadedOut,
        StateFadingIn,
        LastState
    };
    struct ScreenState {
        TimeLine m_timeLine;
        std::chrono::milliseconds m_lastPresentTime = std::chrono::milliseconds::zero();
        FadeOutState m_state = StateNormal;
    };

    void switchState(ScreenState &state);
    void setState(ScreenState &state, FadeOutState newState);
    void addScreen(EffectScreen *screen);
    bool isScreenActive(EffectScreen *screen) const;

    QHash<EffectScreen *, ScreenState> m_waylandStates;
    ScreenState m_xcbState;
    EffectScreen *m_currentScreen = nullptr;
    xcb_atom_t m_atom;
};


} // namespace KWin
#endif // KWIN_KSCREEN_H
