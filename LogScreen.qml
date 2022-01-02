/*!
 *  FILENAME:     LogScreen.qml
 *  DESCRIPTION:  Log File Reader UI main page
 */


import QtQuick 2.15
import QtQuick.Layouts 1.1
import QtQuick.Templates 2.15 as T
import './elements'
import eventLogModel 1.0


Item
{
    id: eventLogScreen
    property string title: "Picture Log Viewer"


    Rectangle {
        anchors.fill: parent
        color: Style.backgroundColor
    }

    EventLogModel
    {
        id: eventLogModel
        property int activeQuery: -1
    }

    /*
     * Model of query types
    //***************** query types model *****************/
    ListModel
    {
        id: headerModel
        ListElement
        {
            text: qsTr("Day")
            query: "-1 day"
        }
        ListElement
        {
            text: qsTr("Week")
            query: "-7 days"
        }
        ListElement
        {
            text: qsTr("Month")
            query: "-1 month"
        }
        ListElement
        {
            text: qsTr("Year")
            query: "-1 year"
        }
    }
    //***************** query types model *****************//

    //********* Buttons for query types model ********//
    ColumnLayout{
        id: top
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.leftMargin: Style.elHorisontalMargin
        anchors.rightMargin: Style.elHorisontalMargin

        RowLayout{
            id: header
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.preferredHeight: Style.eventLogHeaderHeight
            spacing: Style.eventButtonSpacing

            Repeater
            {
                id: queryRepetor
                model:headerModel /* dates from model */
                LogButton{
                    id: index
                    value: model.text
                    property var query: model.query
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                    isActive: (eventLogModel.activeQuery === model.index)
                    onReleased:
                    {
                        console.log("Selected query " + query);
                        eventLogModel.getEventLog(query);
                        eventLogModel.activeQuery = model.index;
                        table.forceLayout();
                    }
                }
            }
        }
        //********* Buttons for query types model ********//

        //*************** [table headers] ***************//
        Row {
            id: columnsHeader
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            anchors.leftMargin: Style.elHorisontalMargin
            anchors.rightMargin: Style.elHorisontalMargin
            Repeater {
                model: table.columns
                Rectangle{
                    height: Style.eventLogTableHeaderHeight
                    width: Style.eventLogColumnWidth[index] /* get width for each column from the qml model */
                    color: Style.headerColor
                    Text {
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.topMargin: Style.eventLogHeaderMargin
                        font.family: Style.fontFamily
                        font.pixelSize: Style.eventLogButtonPixelSize
                        color: Style.textColor
                        anchors.fill: parent
                        maximumLineCount: 2
                        elide: Text.ElideRight
                        wrapMode: Text.WordWrap
                        text:  table.model.headerData(modelData, Qt.Horizontal)
                    }
                }
            }
        }
    }

    //*************** main table ***************//
    TableView {
            id: table
            anchors.top: top.bottom
            anchors.bottom: parent.bottom
            anchors.left: top.left
            anchors.right: top.right
            anchors.bottomMargin: Style.footerHeight
            LogSlider.vertical: LogSlider {visible: (size < 1)}
            columnWidthProvider: function (column) { return Style.eventLogColumnWidth[column] }
            columnSpacing: Style.tableViewColumnSpacing
            rowSpacing: Style.tableViewRowSpacing
            clip: true

            model: eventLogModel

            delegate: Rectangle {
                id: cell
                implicitHeight: Style.tableViewRowHeight
                color: Style.backgroundColor
                Text {
                    id: celltxt
                    anchors.fill: parent
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    font.family: Style.fontFamily
                    font.pixelSize: Style.eventLogButtonPixelSize
                    color: Style.textColor
                    text: display
                    visible: (text === Style.moreInfoCode)?false:true
                }
                PicButton{
                    anchors.centerIn: parent
                    visible: (celltxt.text === Style.moreInfoCode)?true:false
                    value: qsTr("Details");
                    onReleased:{
                        console.log("GET DETAILS : " + eventLogModel.getPictureUrl(model.row));
                        eventLogScreen.T.StackView.view.push(pictureViewScreenPage,
                                                                 {"url": eventLogModel.getPictureUrl(model.row)}
                                                             );
                    }
                }
                Rectangle{
                    anchors.top: cell.bottom
                    anchors.left: cell.left
                    anchors.right: cell.right
                    color: Style.headerColor
                    height: 1
                }
            }
        }
}
