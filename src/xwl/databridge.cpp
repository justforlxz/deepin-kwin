/*
    KWin - the KDE window manager
    This file is part of the KDE project.

    SPDX-FileCopyrightText: 2018 Roman Gilg <subdiff@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "databridge.h"
#include "clipboard.h"
#include "dnd.h"
#include "primary.h"
#include "selection.h"
#include "xwayland.h"

#include "abstract_client.h"
#include "atoms.h"
#include "wayland_server.h"
#include "workspace.h"

#include <DWayland/Server/clientconnection.h>
#include <DWayland/Server/datadevicemanager_interface.h>
#include <DWayland/Server/datadevice_interface.h>
#include <DWayland/Server/seat_interface.h>

using namespace KWaylandServer;

namespace KWin
{
namespace Xwl
{

KWIN_SINGLETON_FACTORY(DataBridge)

void DataBridge::destroy()
{
    delete s_self;
}

DataBridge::DataBridge(QObject *parent)
    : QObject(parent)
{
    s_self = this;
    init();
}

DataBridge::~DataBridge()
{
    s_self = nullptr;
}

void DataBridge::init()
{
    m_clipboard = new Clipboard(atoms->clipboard, this);
    m_dnd = new Dnd(atoms->xdnd_selection, this);
    m_primary = new Primary(atoms->primary, this);
    kwinApp()->installNativeEventFilter(this);
}

bool DataBridge::nativeEventFilter(const QByteArray &eventType, void *message, long int *)
{
    if (eventType == "xcb_generic_event_t") {
        xcb_generic_event_t *event = static_cast<xcb_generic_event_t *>(message);
        return m_clipboard->filterEvent(event) || m_dnd->filterEvent(event) || m_primary->filterEvent(event);
    }
    return false;
}

DragEventReply DataBridge::dragMoveFilter(Toplevel *target, const QPoint &pos)
{
    return m_dnd->dragMoveFilter(target, pos);
}

} // namespace Xwl
} // namespace KWin
