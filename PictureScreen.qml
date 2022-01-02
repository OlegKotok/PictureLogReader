/*!
 * FILENAME:     PictrureScreen.qml
 * DESCRIPTION:  Load picture from external web source
 */

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Templates 2.15 as T
import './elements'


Item
{
    id: pictureScreen
    property string title: (pictureScreen.url[2].length > 0 && bigImage.progress === 1)? pictureScreen.url[2] : "Picture Viewer"

    /*! url[0] - main url,
     *  url[1] - small image
     *  url[2] - description
     */
    property var url: []

    Component.onCompleted: {
        console.log("record is " + pictureScreen.url);
    }

    Image{ /* image preview */
        id: smallImage
        source : pictureScreen.url[1]
        visible: (smallImage.progress === 1 && bigImage.progress !== 0)
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop /*Image.PreserveAspectFit*/
        asynchronous: true
        autoTransform: true
        cache: true

        Rectangle{
            color: Style.backgroundColor
            opacity: 0.5
            anchors.fill: parent
        }
    }

    Image{
        id: bigImage
        source : pictureScreen.url[0]
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop /*Image.PreserveAspectFit*/

        asynchronous: true
        autoTransform: true
        cache: false
    }

    Text /** picture loading progress bar */
    {
        id: progressInfo
        anchors.centerIn: parent

        visible: (color === Style.tempColor) ? false : true;
        text: (bigImage.status === Image.Null) ? "No image has been set" :
              (bigImage.status === Image.Error) ? "Loading image error" :
              (bigImage.progress===0) ? "Loading..." : Math.trunc(bigImage.progress * 100) + "%"
        font.pixelSize: Style.progressTextPixelSize
        color: Style.progressColor

        horizontalAlignment: Text.AlignHCenter
    }

    ColorAnimation {
      target: progressInfo
      properties: "color"
      to: Style.tempColor
      duration: 800
      running: (bigImage.progress === 1) ? true : false; /** run animation when whole pictures is fully loaded */
      easing.type: Easing.InQuad
    }
}

