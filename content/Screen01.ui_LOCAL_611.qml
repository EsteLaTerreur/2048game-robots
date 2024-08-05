

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import Jeu2048
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: 500
    height: 500
    color: "#d875ff"
    border.color: "#791770"
    border.width: 3

    Rectangle {
        id: rectangle1
        width: 390
        height: 386
        color: "#edc0ff"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        GridLayout {
            id: grid
            anchors.fill: parent
            columns: 4
            rows: 4

            Rectangle {
                id: rec0
                width: 20
                height: 20
                color: "white"
                Column: 0
                Text {
                    text: 0
                }
            }
            Rectangle {
                id: rec1
                width: 20
                height: 20
                color: "white"
                Column: 0
                Text {
                    text: 0
                }
            }
        }
    }
}
