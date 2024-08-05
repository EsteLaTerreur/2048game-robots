

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
    height: 700
    color: "#d875ff"
    border.color: "#791770"
    border.width: 3

    Popup {
        id: popupFin
        anchors.centerIn: parent
        width: 300
        height: 200
        modal: true
        focus: true
        background: Rectangle {
            color: "#d875ff"
            radius: 10
        }
        contentItem: ColumnLayout {
            anchors.fill: parent
            spacing: 10

            Text {
                text: "Fin de la partie, vous avez perdu !"
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Text {
                text: " Cliquez pour relancer une partie :"
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                id: buttonRestart2
                height: 30
                width: 50
                text: qsTr("NEW")
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    color: "#c43e3e"
                    radius: 10
                }
                onClicked: {
                    popupFin.close()
                    console.log("Nouvelle partie")
                    grid.forceActiveFocus()
                    listeDeCases.nouveaujeu()
                }
            }
            Text {
                text: "Ou annulez votre dernier coup :"
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Button {
                id: buttonUndo2
                height: 30
                width: 50
                text: qsTr("UNDO")
                Layout.alignment: Qt.AlignHCenter
                font.bold: true
                background: Rectangle {
                    color: "#c43e3e"
                    radius: 10
                }
                onClicked: {
                    popupFin.close()
                    console.log("UNDO")
                    grid.forceActiveFocus()
                    listeDeCases.lireFichier(
                                "../Jeu2048/src/parties/coup_precedent_pour_undo.txt")
                }
            }
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }
    Rectangle {
        id: rectangle1
        width: 385
        height: 385
        color: "#edc0ff"
        radius: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 30
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        GridLayout {
            id: grid
            anchors.fill: parent
            anchors.leftMargin: 8
            anchors.rightMargin: 4
            anchors.topMargin: 5
            anchors.bottomMargin: 5
            rows: 4
            columns: 4
            columnSpacing: 1
            rowSpacing: 1
            focus: true
            Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Up:
                    console.log('key up')
                    listeDeCases.tour(0)
                    listeDeCases.partie_terminee ? popupFin.open(
                                                       ) : console.log(
                                                       'tour suivant')
                    break
                case Qt.Key_Right:
                    console.log('key right')
                    listeDeCases.tour(1)
                    listeDeCases.partie_terminee ? popupFin.open(
                                                       ) : console.log(
                                                       'tour suivant')
                    break
                case Qt.Key_Down:
                    console.log('key down')
                    listeDeCases.tour(2)
                    listeDeCases.partie_terminee ? popupFin.open(
                                                       ) : console.log(
                                                       'tour suivant')
                    break
                case Qt.Key_Left:
                    console.log('key left')
                    listeDeCases.tour(3)
                    listeDeCases.partie_terminee ? popupFin.open(
                                                       ) : console.log(
                                                       'tour suivant')
                    break
                }
            }

            Rectangle {
                id: rect0
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                color: case0.caseCouleur
                // partie animation
                Connections {
                    target: case0
                    onAnimation: {
                        rect0.width = 93
                        rect0.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                // partie affichage de la valeur
                Text {
                    id: text0
                    text: case0.caseValeur == 1 ? '' : case0.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect1
                color: case1.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case1
                    onAnimation: {
                        rect1.width = 93
                        rect1.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text1
                    text: case1.caseValeur == 1 ? '' : case1.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect2
                color: case2.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case2
                    onAnimation: {
                        rect2.width = 93
                        rect2.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text2
                    text: case2.caseValeur == 1 ? '' : case2.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect3
                color: case3.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case3
                    onAnimation: {
                        rect3.width = 93
                        rect3.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text3
                    text: case3.caseValeur == 1 ? '' : case3.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect4
                color: case4.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case4
                    onAnimation: {
                        rect4.width = 93
                        rect4.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text4
                    text: case4.caseValeur == 1 ? '' : case4.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect5
                color: case5.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case5
                    onAnimation: {
                        rect5.width = 93
                        rect5.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text5
                    text: case5.caseValeur == 1 ? '' : case5.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect6
                color: case6.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case6
                    onAnimation: {
                        rect6.width = 93
                        rect6.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text6
                    text: case6.caseValeur == 1 ? '' : case6.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect7
                color: case7.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case7
                    onAnimation: {
                        rect7.width = 93
                        rect7.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text7
                    text: case7.caseValeur == 1 ? '' : case7.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect8
                color: case8.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case8
                    onAnimation: {
                        rect8.width = 93
                        rect8.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text8
                    text: case8.caseValeur == 1 ? '' : case8.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect9
                color: case9.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case9
                    onAnimation: {
                        rect9.width = 93
                        rect9.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text9
                    text: case9.caseValeur == 1 ? '' : case9.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect10
                color: case10.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case10
                    onAnimation: {
                        rect10.width = 93
                        rect10.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text10
                    text: case10.caseValeur == 1 ? '' : case10.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect11
                color: case11.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case11
                    onAnimation: {
                        rect11.width = 93
                        rect11.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text11
                    text: case11.caseValeur == 1 ? '' : case11.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect12
                color: case12.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case12
                    onAnimation: {
                        rect12.width = 93
                        rect12.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text12
                    text: case12.caseValeur == 1 ? '' : case12.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect13
                color: case13.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case13
                    onAnimation: {
                        rect13.width = 93
                        rect13.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text13
                    text: case13.caseValeur == 1 ? '' : case13.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect14
                color: case14.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case14
                    onAnimation: {
                        rect14.width = 93
                        rect14.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text14
                    text: case14.caseValeur == 1 ? '' : case14.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle {
                id: rect15
                color: case15.caseCouleur
                radius: 15
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                Layout.preferredWidth: 88
                Layout.preferredHeight: 88
                // partie animation
                Connections {
                    target: case15
                    onAnimation: {
                        rect15.width = 93
                        rect15.height = 93
                    }
                }
                Behavior on width {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Behavior on height {
                    SequentialAnimation {
                        NumberAnimation {
                            from: 88
                            to: 93
                            duration: 80
                        }
                        NumberAnimation {
                            from: 93
                            to: 88
                            duration: 80
                        }
                    }
                }
                Text {
                    id: text15
                    text: case15.caseValeur == 1 ? '' : case15.caseValeur
                    anchors.fill: parent
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    Rectangle {
        id: rectangleMenus
        x: 28
        y: 44
        width: 443
        height: 129
        color: "#edc0ff"
        radius: 10

        GridLayout {
            id: grilleMenu
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            rows: 2
            columns: 4
            Rectangle {
                id: rectangleMeilleureTuile
                Layout.rowSpan: 2
                Layout.columnSpan: 1
                width: 109
                color: listeDeCases.meilleure_couleur
                radius: 10
                Layout.fillWidth: false
                Layout.fillHeight: true
                Text {
                    id: textMeilleureTuile
                    width: 95
                    height: 47
                    text: listeDeCases.meilleure_tuile
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    anchors.verticalCenterOffset: 0
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            Rectangle {
                id: rectangleScore
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                width: 98
                height: 52
                color: "#7c32aa"
                radius: 10
                GridLayout {
                    id: gridScore
                    anchors.fill: parent
                    flow: GridLayout.LeftToRight
                    rows: 2
                    columns: 1
                    rowSpacing: 0
                    columnSpacing: 0
                    Text {
                        id: textScore
                        text: qsTr("Score :")
                        font.pixelSize: 17
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                    Text {
                        id: score
                        text: listeDeCases.score
                        font.pixelSize: 17
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignTop
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
            Rectangle {
                id: rectangleHighScore
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                width: 98
                height: 52
                color: "#7c32aa"
                radius: 10
                GridLayout {
                    id: gridMeilleurScore
                    anchors.fill: parent
                    flow: GridLayout.LeftToRight
                    rows: 2
                    columns: 1
                    rowSpacing: 0
                    columnSpacing: 0
                    Text {
                        id: textMeilleurScore
                        text: qsTr("Best score :")
                        font.pixelSize: 17
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                    Text {
                        id: meilleurScore
                        text: listeDeCases.bestscore
                        font.pixelSize: 17
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignTop
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
            Button {
                id: buttonpalette
                Layout.rowSpan: 2
                Layout.columnSpan: 1
                x: 100
                y: 50
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    text: qsTr("Couleur palette")
                }
                font.bold: true
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                background: Rectangle {
                    color: "#B14068"
                    radius: 10
                }
                onClicked: {
                    console.log("Nouvelle palette")
                    grid.forceActiveFocus()
                    listeDeCases.nouvellepalette()
                }
            }
            Button {
                id: buttonRestart
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                x: 130
                y: 67
                text: qsTr("NEW")
                font.bold: true
                Layout.fillHeight: false
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                background: Rectangle {
                    color: "#C43E3E"
                    radius: 10
                }
                onClicked: {
                    console.log("Nouvelle partie")
                    grid.forceActiveFocus()
                    listeDeCases.nouveaujeu()
                }
            }

            Button {
                id: buttonUndo
                Layout.rowSpan: 1
                Layout.columnSpan: 1
                x: 232
                y: 69
                text: qsTr("UNDO")
                font.bold: true
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                background: Rectangle {
                    color: "#C43E3E"
                    radius: 10
                }
                onClicked: {
                    console.log("UNDO")
                    grid.forceActiveFocus()
                    listeDeCases.lireFichier(
                                "../Jeu2048/src/parties/coup_precedent_pour_undo.txt")
                }
            }
        }
    }
    ColumnLayout{
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin: 1
            topMargin: 1
        }
        RowLayout {
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottomMargin: 1
                topMargin: 1
            }
            Button {
                id: buttonRobot0
                x: 232
                y: 69
                text: qsTr("Robot random")
                font.bold: true

                background: Rectangle {
                    color: "#C43E3E"
                    radius: 10
                }
                onClicked: {
                    grid.forceActiveFocus()
                    listeDeCases.lanceRobot0()
                }
            }
            Button {
                id: buttonRobot1
                x: 232
                y: 69
                text: qsTr("Robot score")
                font.bold: true

                background: Rectangle {
                    color: "#C43E3E"
                    radius: 10
                }
                onClicked: {
                    grid.forceActiveFocus()
                    listeDeCases.lanceRobot1()
                }
            }
            Button {
                id: buttonRobot2
                x: 232
                y: 69
                text: qsTr("Robot fusion")
                font.bold: true

                background: Rectangle {
                    color: "#C43E3E"
                    radius: 10
                }
                onClicked: {
                    grid.forceActiveFocus()
                    listeDeCases.lanceRobot2()
                }
            }
        }

        RowLayout {
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottomMargin: 1
                topMargin: 1
            }
            Button {
                id: buttonRobot3
                x: 232
                y: 69
                text: qsTr("Meilleur robot")
                font.bold: true

                background: Rectangle {
                    color: "#C43E3E"
                    radius: 10
                }
                onClicked: {
                    grid.forceActiveFocus()
                    listeDeCases.lanceRobot3()
                }
            }
            Button {
                id: buttonRobotPause
                x: 232
                y: 69
                text: qsTr("Pause")
                font.bold: true

                background: Rectangle {
                    color: "#C43E3E"
                    radius: 10
                }
                onClicked: {
                    grid.forceActiveFocus()
                    listeDeCases.pauseRobot()
                }
            }
        }
    }

    Connections {
        target: listeDeCases
        onPopup: {
            popupFin.open()
        }
    }
}
