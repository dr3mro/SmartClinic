import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import Sc_assistant.BackEnd 1.0


RoundButton {
    id:addButton
    z:100
    icon.color: "transparent"
    icon.source : "qrc:/addIcon"
    visible:true
    enabled: true
    radius: 96
    height: 72
    width:  72
    onClicked: {
        stack.pop()
        stack.push(addVisitor)
        menuBackIcon.state = "back"
        addButton.visible = false
    }
    anchors.bottom:stack.bottom
    anchors.right: stack.right
    anchors.rightMargin: 20
    anchors.bottomMargin: 20
    //padding: 12
}
