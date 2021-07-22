import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.0
Item {
    property alias serverIP : server.text
    ColumnLayout {
        width: parent.width
        height:parent.height

        Button {
            text: qsTr("Clear")
            Layout.alignment: Qt.AlignHCenter

            onClicked:{
                messageDialogText=qsTr("Are you sure you want to delete all")
                var messageDlg = messageDialog.createObject(parent)
                messageDlg.yes.connect(function(){
                    backend.deleteAll()
                })
            }
        }

        Rectangle{
            Layout.fillHeight: true
        }

        RowLayout{
            id : serverDetails
            Layout.alignment: Qt.AlignHCenter
            Text {
                id:label
                text: "Server IP Address:"
                color:"Yellow"
            }
            TextInput {
                id: server
                text: serverIP
                readOnly: true
                color: connected ? "Green" : "Red"
            }
        }
        Text {
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 24
            text: connected ? "CONNECTED" : "DISCONNECTED"
            color: connected ? "Green" : "Red"
        }
    }
}
