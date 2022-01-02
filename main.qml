/*!
 *  FILENAME:     main.qml
 *  DESCRIPTION:  Application main window implementation with StackView panel
 */


import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Templates 2.15 as T
import './elements'


T.ApplicationWindow
{
    id: applicationWindow
    visible: true
    width: 1024
    height: 600

    title: qsTr("Picture Log Viewer")

    color: Style.backgroundColor

    property bool isHorizontal:
        Screen.primaryOrientation === Qt.LandscapeOrientation ||
        Screen.primaryOrientation === Qt.InvertedLandscapeOrientation;

    onIsHorizontalChanged:
    {
        if (isHorizontal)
        {
            // landscape
            console.log("landscape");
        }
        else
        {
            // portrait
            console.log("portrait");
        }
    }

    Rectangle
    {
        id: header

        anchors.top: parent.top
        height: Style.headerHeight
        width: parent.width

        color: headerTitle.text === "" ? Style.transparent : Style.headerColor

        //Header title
        Text
        {
            id: headerTitle
            anchors.verticalCenter: header.verticalCenter
            anchors.left: header.right
            anchors.horizontalCenter: header.horizontalCenter

            text: stackView.currentItem.title
            font.pixelSize: Style.headerTitlePixelSize
            color: Style.textColor

            horizontalAlignment: Text.AlignHCenter
        }
    }

    // PageStack
    T.StackView
    {
        id: stackView
        anchors
        {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: header.bottom
        }
        background: Rectangle
        {
            anchors.fill: stackView
            color: Style.backgroundColor
        }

        Component{
            id: eventLogScreenPage
            LogScreen{}
        }

        Component{
            id: pictureViewScreenPage
            PictureScreen{
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stackView.pop();
                    }
                }
            }
        }

        initialItem: eventLogScreenPage

    }
}

