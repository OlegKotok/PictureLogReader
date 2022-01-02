/*!
 * FILENAME:     LogSlider.qml
 * DESCRIPTION:  Non-interactive indicator for long ListViews
 */

import QtQuick 2.15
import QtQuick.Templates 2.15 as T


T.ScrollIndicator
{
    id: control

    implicitWidth: 10
    implicitHeight: 10

    background: Rectangle
    {
        id: background
        implicitWidth: parent.implicitWidth
        implicitHeight: control.availableHeight
        radius: implicitHeight / 2
        color: Style.headerColor
        anchors.fill: parent
    }

    contentItem: Rectangle
    {
        id: scroller
        implicitHeight: control.availableHeight
        implicitWidth: control.availableWidth
        radius: implicitHeight / 2
        color: Style.buttonColor
    }
}
