

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import Jeu2048

Rectangle {
    id: rectangle
    width: 320
    height: 240
    color: "#d875ff"
    border.color: "#791770"
    border.width: 3

    Rectangle {
        id: rectangle1
        x: 102
        width: 100
        height: 50
        color: "#874cdc"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: text1
            text: vueObjetCpt.cptQML
            Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Up:
                    vueObjetCpt.increment()
                    break
                case Qt.Key_Down:
                    vueObjetCpt.decrement()
                    break
                }
            }
            anchors.fill: parent
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            focus: true
            font.styleName: "Gras"
            font.family: "Tahoma"
        }
    }
}
