pragma Singleton
import QtQuick 2.15

QtObject
{
    // COLORS
    readonly property color  backgroundColor: "#FF323232"
    readonly property color  textColor: "#FFFFFFFF"
    readonly property color  progressColor: "#AADDDDDD"
    readonly property color  headerColor: "#FF000000"
    readonly property color  tempColor: "#08AAAAAA"
    readonly property color  transparent: "#00000000"
    readonly property int    headerHeight: 90

    // FONTS & FONT SIZES
    readonly property string fontFamily: "Noto Sans"
    readonly property int    headerTitlePixelSize: 30
    readonly property int    progressTextPixelSize: 80
    readonly property int    eventLogButtonPixelSize: 16

    //EVENTLOG
    readonly property int    tableViewColumnSpacing: 0
    readonly property int    tableViewRowSpacing: 1
    readonly property int    tableViewRowHeight: 40
    readonly property int    elTopMargin: 20
    readonly property int    elHorisontalMargin: 50
    readonly property var    eventLogColumnWidth: [50, 120, 100, 300, 150, 200]
    readonly property int    eventLogRowBorder: 1
    readonly property int    eventLogButtonWidth: 135
    readonly property int    eventLogButtonHeight: 40
    readonly property int    eventLogHeaderHeight: 65
    readonly property int    eventButtonSpacing: 8
    readonly property int    eventLogTableHeaderHeight: 60
    readonly property string moreInfoCode: "#MOREINFO"
    readonly property int    eventLogButtonDetailsWidth: 160
    readonly property int    eventLogButtonDetailsHeight: 85
    readonly property int    eventLogDetailsSpacing: 25

    //BUTTONS
    readonly property real   btIdleOpacity: 1.0
    readonly property color  buttonColor: "#FF646464"
    readonly property color  btGreenColor: "#64c832"
    readonly property color  btBlueColor: "#0196FA"
    readonly property color  btBgColor: "#7F7F7F"
    readonly property color  btYellowColor: "#FA9601"
    readonly property real   btTouchedOpacity: 0.9
}
