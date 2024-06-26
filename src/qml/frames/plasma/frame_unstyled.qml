/*
    SPDX-FileCopyrightText: 2022 MBition GmbH
    SPDX-FileContributor: Kai Uwe Broulik <kai_uwe.broulik@mbition.io>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

import QtQuick 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4 as QQC2

import org.kde.kirigami 2.5 as Kirigami

Rectangle {
    id: root

    property QtObject effectFrame: null

    implicitWidth: layout.implicitWidth + 2 * layout.anchors.margins
    implicitHeight: layout.implicitHeight + 2 * layout.anchors.margins

    color: Qt.rgba(0, 0, 0, effectFrame.frameOpacity)
    radius: layout.anchors.margins

    RowLayout {
        id: layout
        anchors {
            fill: parent
            margins: layout.spacing
        }
        spacing: 5

        Kirigami.Icon {
            id: icon
            Layout.preferredWidth: root.effectFrame.iconSize.width
            Layout.preferredHeight: root.effectFrame.iconSize.height
            Layout.alignment: Qt.AlignHCenter
            visible: true
            source: root.effectFrame.icon
        }

        QQC2.Label {
            id: label
            Layout.fillWidth: true
            color: "white"
            textFormat: Text.PlainText
            elide: Text.ElideRight
            font: root.effectFrame.font
            visible: text !== ""
            text: root.effectFrame.text
        }
    }
}
