/*!  FILENAME:  LogButton.qml
 *   DESCRIPTION: Multicolor and multi-state button
 */

import QtQuick 2.15
import QtQuick.Templates 2.15 as T

T.Button
{
    id: control
    state: "gray"
    property alias color: backgroundRect.color
    property alias value: txt.text
    property bool isActive: false

    property var previusState: state

    implicitWidth: Style.eventLogButtonWidth
    implicitHeight: Style.eventLogButtonHeight

    background:Item{
        Rectangle {
            id: backgroundRect
            radius: Style.eventLogButtonHeight / 2
            color:  Style.btBgColor
            anchors.fill: parent
        }
        MouseArea {
            id: mouser
            anchors.fill: parent
            hoverEnabled: true
        }

        states: State {
            name: "GreenState"
            when: mouser.containsMouse

            PropertyChanges {
                target: backgroundRect
                color: Style.btGreenColor
            }
        }

        transitions: Transition {
            ColorAnimation {}
        }
    }

    Text {
        id: txt
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Style.fontFamily
        font.pixelSize: Style.eventLogButtonPixelSize
        color: Style.headerColor
        anchors.fill: parent
        maximumLineCount: 1
        elide: Text.ElideRight
        wrapMode: Text.WordWrap
    }

    onIsActiveChanged:
    {
        control.state = (isActive)?"blue":"gray"
    }

    onPressed:
    {
        control.previusState = control.state;
        control.state = "touched";
    }

    onReleased:
    {
        control.state = control.previusState
    }

    onCanceled:
    {
        control.state = control.previusState
    }

    states:
        [
        State
        {
            name: "idle"
            PropertyChanges
            {
                target: control
                opacity: Style.circleButtonIdleOpacity
            }
        },
        State
        {
            name: "touched"
            PropertyChanges
            {
                target: control
                opacity: Style.btTouchedOpacity
                color: Style.btYellowColor
            }
        },
        State
        {
            name: "gray"
            PropertyChanges
            {
                target: control
                opacity: Style.btIdleOpacity
                color: Style.btBgColor
            }
        },
        State
        {
            name: "blue"
            PropertyChanges
            {
                target: control
                color: Style.btBlueColor
                opacity: Style.btIdleOpacity
            }
        },
        State
        {
            name: "green"
            PropertyChanges
            {
                target: control
                color: Style.btGreenColor
                opacity: Style.btIdleOpacity

            }
        }
    ]
}
