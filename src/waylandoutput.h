/*
    SPDX-FileCopyrightText: 2021 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "abstract_wayland_output.h"

#include <DWayland/Server/output_interface.h>
#include <DWayland/Server/xdgoutput_v1_interface.h>
#include <DWayland/Server/utils.h>

namespace KWin
{

class WaylandOutput : public QObject
{
    Q_OBJECT

public:
    explicit WaylandOutput(AbstractWaylandOutput *output, QObject *parent = nullptr);

    KWaylandServer::OutputInterface *waylandOutput() const{
        return m_waylandOutput.data();
    };

private Q_SLOTS:
    void handleDpmsModeChanged();
    void handleDpmsModeRequested(KWaylandServer::OutputInterface::DpmsMode dpmsMode);

    void update();
    void scheduleUpdate();

private:
    AbstractWaylandOutput *m_platformOutput;
    QTimer m_updateTimer;
    KWaylandServer::ScopedGlobalPointer<KWaylandServer::OutputInterface> m_waylandOutput;
    KWaylandServer::XdgOutputV1Interface *m_xdgOutputV1;
};

} // namespace KWin
