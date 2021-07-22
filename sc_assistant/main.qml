import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import Sc_assistant.BackEnd 1.0


ApplicationWindow {
    id: mainwindow

    BackEnd {
        id: backend
    }
    AddButton {
        id: addButton
    }

    Component{
        id: messageDialog
        MessageDialog {
            id:dialog
            text: messageDialogText
            onVisibleChanged: if(!visible) destroy(1)
            standardButtons: StandardButton.Yes | StandardButton.No
            icon: StandardIcon.Question
            Component.onCompleted:
            {
                visible = true
                messageDialog.standardButton(dialog.Yes).text=qsTr("Yes")
                messageDialog.standardButton(dialog.No).text=qsTr("No")
            }
        }
    }


    property int visitorIndex: -1
    property alias visitorName: backend.name
    property alias visitorId: backend.ID
    property alias visitorAge: backend.age
    property alias visitorSex: backend.sex
    property alias visitorMarital: backend.marital
    property alias visitorResidence: backend.residence
    property alias visitorPlaceofbirth: backend.placeofbirth
    property alias visitorJob: backend.job
    property alias visitorTel: backend.tel
    property alias visitorVisitType: backend.visitType
    property string messageDialogText
    property alias serverIP:backend.serverIP
    property alias connected: backend.isConnected
    property var finisedSate

    width: 320
    height:620
    visible: true

    header: ToolBar {
        id: headerBar
        Material.primary: connected ? Material.Green : Material.Red
        RowLayout {
            width:header.width

            Label {
                text:"SmartClinic Assistant"
                Layout.alignment: Qt.AlignCenter
            }

            Rectangle {
                Layout.alignment: Qt.AlignRight
                width: 48
                height: 48
                color: connected? "green":"red"
                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        menuBackIcon.state = menuBackIcon.state === "menu" ? "back" : "menu"
                        stack.pop()
                        if (menuBackIcon.state === "menu"){
                            stack.pop()
                            stack.push(peopleList)
                            addButton.visible = true
                        }
                        else{
                            addButton.visible = false
                            stack.pop()
                            stack.push(menu)
                        }

                    }

                }

                MenuBackIcon {
                    id: menuBackIcon
                    anchors.centerIn: parent

                }
            }

        }
    }


    StackView {
        id: stack
        initialItem: peopleList
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        Component{
            id: peopleList
            PeopleList {
            }
        }

        Component{
            id:menu
            Ui_Menu{
                serverIP: backend.serverIP
            }
        }

        Component{
            id:addVisitor

            Ui_VisitorEditor{
                del_btn.visible :false

                save_btn.onClicked: {
                    backend.name = visitorName
                    backend.ID = visitorID
                    backend.age = visitorAge
                    backend.sex = visitorSex
                    backend.marital = visitorMarital
                    backend.residence = visitorResidence
                    backend.placeofbirth = visitorPlaceofbirth
                    backend.tel = visitorTel
                    backend.visitType = visitorVisitType
                    backend.job = visitorJob
                    backend.finished = false
                    backend.addNew(-1)
                    addButton.visible = true
                    menuBackIcon.state = "menu"
                    stack.pop()
                    stack.push(peopleList)
                }
            }
        }

        Component{
            id:editVisitor
            Ui_VisitorEditor{

                visitorID : backend.ID
                visitorName : backend.name
                visitorAge: backend.age
                visitorSex: backend.sex
                visitorMarital: backend.marital
                visitorResidence: backend.residence
                visitorPlaceofbirth: backend.placeofbirth
                visitorTel: backend.tel
                visitorVisitType: backend.visitType
                visitorJob: backend.job


                save_btn.onClicked: {
                    backend.name = visitorName
                    backend.ID = visitorID
                    backend.age = visitorAge
                    backend.sex = visitorSex
                    backend.marital = visitorMarital
                    backend.residence = visitorResidence
                    backend.placeofbirth = visitorPlaceofbirth
                    backend.tel = visitorTel
                    backend.visitType = visitorVisitType
                    backend.job = visitorJob
                    backend.finished = finisedSate
                    backend.delVisitor(visitorIndex)
                    backend.addNew(visitorIndex)
                    stack.pop()
                    stack.push(peopleList)
                    addButton.visible = true
                    menuBackIcon.state = "menu"
                }
            }

        }
    }

}

