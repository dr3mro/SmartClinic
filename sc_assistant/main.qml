import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import Sc_assistant.BackEnd 1.0

ApplicationWindow {
    id: mainwindow
    BackEnd {
        id: backend
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

    width: 320
    height:620
    visible: true

    header: ToolBar {
        id: headerBar
        RowLayout {
            width: parent.width
            ToolButton {
                id:backButton
                text: qsTr(" ")
                visible:true
                enabled: false
                onClicked: {
                    stack.pop()
                    if (stack.depth === 1){
                        backButton.text=qsTr(" ")
                        backButton.enabled=false
                        mFooter.visible=true

                    }


                }
            }

            Label {
                text:"SmartClinic Assistant"
                elide: Label.ElideRight
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                Layout.fillWidth: true
            }
            ToolButton {
                text: qsTr("⋮")
                onClicked: {
                    stack.push(settingsDialog)

                }
            }
        }
    }


    StackView {
        id: stack
        initialItem: initialView
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        Component{
            id:settingsDialog
            ColumnLayout {
                id: settings

                Text {
                    id:label
                    Layout.alignment:Qt.AlignHCenter | Qt.AlignVCenter
                    text: "server"
                    color:"Yellow"
                    height: 40
                    anchors.bottom: server.top
                }
                TextField {
                    Layout.alignment:Qt.AlignHCenter | Qt.AlignVCenter
                    id: server
                    width: parent.width
                    focus: true
                    text:serverIP
                }
                Row{
                    anchors.top: server.bottom
                    Layout.alignment:Qt.AlignHCenter | Qt.AlignVCenter
                    spacing: 10
                    Button{
                        text:qsTr("save")
                        onClicked: {
                            backend.serverIP=server.text
                            stack.pop()
                        }
                    }
                    Button{
                        text:qsTr("cancel")
                        onClicked: {
                            stack.pop()
                        }
                    }
                }
            }
        }


        Component{
            id:peopleList

            ScrollView {
                id:scroll
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView {
                    id:list
                    model: backend.getPeopleList()

                    delegate: ItemDelegate {
                        id:listdelegate
                        width: parent.width

                        Text {
                            text: modelData
                            color: "#ffffff"
                            anchors.centerIn: parent

                        }

                        onClicked: {
                            list.currentIndex = index
                            visitorIndex = index
                            backend.loadVisitor(visitorIndex)
                            stack.push(editVisitor)
                            backButton.text="‹"
                            backButton.enabled=true
                            mFooter.visible=false
                        }
                    }

                }
            }
        }


        Component{
            id:initialView

            ColumnLayout{

                Button{
                    text:qsTr("Add Visitor")
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: {
                        stack.pop()
                        stack.push(addVisitor)
                        backButton.text="‹"
                        backButton.enabled=true
                        mFooter.visible=false
                    }
                }
                Button{
                    text:qsTr("Show All")
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: {
                        stack.pop()
                        stack.push(peopleList)
                        backButton.text="‹"
                        backButton.enabled=true
                        mFooter.visible=false
                    }
                }
            }
        }


        Component{
            id:addVisitor
            ScrollView{
                id:addVisitorScroll

                ColumnLayout{
                    width:addVisitorScroll.width

                    RowLayout{

                        Label{
                            text: qsTr("ID")

                        }
                        TextField{
                            id:visitorID
                            placeholderText: qsTr("Visitor ID")
                            Layout.fillWidth: true
                        }

                    }


                    RowLayout{
                        width: addVisitorScroll.width
                        Label{
                            text: qsTr("Name")
                        }
                        TextField{
                            id:name
                            placeholderText: qsTr("Visitor Name")
                            Layout.fillWidth: true


                        }

                    }


                    RowLayout{
                        width: addVisitorScroll.width
                        Label{
                            text: qsTr("Age")
                        }
                        SpinBox{
                            id:age
                            Layout.fillWidth: true
                            editable: true

                        }

                    }




                    RowLayout{
                        width: addVisitorScroll.width
                        Label{
                            text: qsTr("Sex")

                        }
                        ComboBox{
                            id:sex
                            model: [ qsTr("Male"),  qsTr("Female")]
                            Layout.fillWidth: true
                        }

                    }


                    RowLayout{
                        width: addVisitorScroll.width
                        Label{
                            text: qsTr("Marital")

                        }
                        ComboBox{
                            id:marital
                            model: [ qsTr("Single"),qsTr("Married"),qsTr("Widdowed"),qsTr("Devorced")]
                            Layout.fillWidth: true

                        }

                    }




                    RowLayout{
                        width: addVisitorScroll.width
                        Label{
                            text: qsTr("Residence")

                        }
                        TextField{
                            id:residence
                            placeholderText: qsTr("Residence")
                            Layout.fillWidth: true


                        }

                    }



                    RowLayout{
                        width: addVisitorScroll.width
                        Label{
                            text: qsTr("Place of birth")

                        }
                        TextField{
                            id:placeofbirth
                            placeholderText: qsTr("Place of birth")
                            Layout.fillWidth: true


                        }

                    }
                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Job")

                        }
                        TextField{
                            id:job
                            placeholderText: qsTr("Job")
                            Layout.fillWidth: true

                        }

                    }


                    RowLayout{
                        width: addVisitorScroll.width
                        Label{
                            text: qsTr("Tel")
                        }
                        TextField{
                            id:mobile
                            placeholderText: qsTr("Telephone")
                            Layout.fillWidth: true


                        }

                    }


                    RowLayout{
                        width: addVisitorScroll.width
                        Label{
                            text: qsTr("Visit Type")

                        }
                        ComboBox{
                            id:visitType
                            model: [ qsTr("New"),qsTr("follow1"),qsTr("follow2"),qsTr("follow3"),qsTr("follow4"),qsTr("free")]
                            Layout.fillWidth: true
                        }

                    }



                    Button{
                        id:save
                        text:qsTr("Save")
                        Layout.alignment: Qt.AlignHCenter
                        Material.background: "Green"


                        onClicked: {

                            backend.name = name.text;
                            backend.ID = visitorID.text;
                            backend.age = age.value;
                            backend.sex = sex.currentIndex;
                            backend.marital = marital.currentIndex;
                            backend.residence = residence.text
                            backend.placeofbirth = placeofbirth.text
                            backend.tel = mobile.text;
                            backend.visitType = visitType.currentIndex;
                            backend.job = job.text
                            backend.addNew(-1)
                            stack.pop()
                            mFooter.visible=true
                        }
                    }


                }







            }
        }

        Component{


            id:editVisitor

            ScrollView{
                id:editVisitorScroll

                ColumnLayout{
                    width:editVisitorScroll.width

                    RowLayout{

                        Label{
                            text: qsTr("ID")

                        }
                        TextField{
                            id:visitorID
                            placeholderText: qsTr("Visitor ID")
                            Layout.fillWidth: true
                            text: visitorId

                        }

                    }


                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Name")
                        }
                        TextField{
                            id:name
                            placeholderText: qsTr("Visitor Name")
                            Layout.fillWidth: true
                            text:visitorName
                        }

                    }


                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Age")
                        }
                        SpinBox{
                            id:age
                            Layout.fillWidth: true
                            editable: true
                            value: visitorAge
                        }

                    }




                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Sex")

                        }
                        ComboBox{
                            id:sex
                            model: [ qsTr("Male"),  qsTr("Female")]
                            Layout.fillWidth: true
                            currentIndex: visitorSex
                        }

                    }


                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Marital")

                        }
                        ComboBox{
                            id:marital
                            model: [ qsTr("Single"),qsTr("Married"),qsTr("Widdowed"),qsTr("Devorced")]
                            Layout.fillWidth: true
                            currentIndex: visitorMarital
                        }

                    }




                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Residence")

                        }
                        TextField{
                            id:residence
                            placeholderText: qsTr("Residence")
                            Layout.fillWidth: true
                            text: visitorResidence

                        }

                    }



                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Place of birth")

                        }
                        TextField{
                            id:placeofbirth
                            placeholderText: qsTr("Place of birth")
                            Layout.fillWidth: true
                            text: visitorPlaceofbirth

                        }

                    }

                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Job")

                        }
                        TextField{
                            id:job
                            placeholderText: qsTr("Job")
                            Layout.fillWidth: true
                            text: visitorJob

                        }

                    }

                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Tel")
                        }
                        TextField{
                            id:mobile
                            placeholderText: qsTr("Telephone")
                            Layout.fillWidth: true
                            text: visitorTel

                        }

                    }


                    RowLayout{
                        width: editVisitorScroll.width
                        Label{
                            text: qsTr("Visit Type")

                        }
                        ComboBox{
                            id:visitType
                            model: [ qsTr("New"),qsTr("follow1"),qsTr("follow2"),qsTr("follow3"),qsTr("follow4"),qsTr("free")]
                            Layout.fillWidth: true
                            currentIndex: visitorVisitType
                        }

                    }

                    RowLayout{
                        width: editVisitorScroll.width
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                        Button{
                            id:save
                            text:qsTr("Save")
                            Layout.alignment: Qt.AlignHCenter
                            Material.background: "Green"


                            onClicked: {
                                backend.name = name.text;
                                backend.ID = visitorID.text;
                                backend.age = age.value;
                                backend.sex = sex.currentIndex;
                                backend.marital = marital.currentIndex;
                                backend.residence = residence.text
                                backend.placeofbirth = placeofbirth.text
                                backend.job = job.text
                                backend.tel = mobile.text;
                                backend.visitType = visitType.currentIndex;
                                backend.delVisitor(visitorIndex)
                                backend.addNew(visitorIndex)
                                stack.pop()
                                stack.pop()
                                stack.push(peopleList)
                            }
                        }


                        Button{
                            id:deleteVisitor
                            text:qsTr("Delete")
                            Layout.alignment: Qt.AlignHCenter
                            Material.background: "red"
                            onClicked: {
                                messageDialogText=qsTr("Are you sure you want to delete this visitor")
                                var messageDlg = messageDialog.createObject(parent)
                                messageDlg.yes.connect(function(){
                                    backend.delVisitor(visitorIndex)
                                    stack.pop()
                                    stack.pop()
                                    stack.push(peopleList)
                                })

                            }
                        }
                    }
                }
            }
        }
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




    footer: ToolBar {
        id:mFooter
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("Push")
                Layout.alignment: Qt.AlignLeft
                onClicked:{
                    backend.send()
                }
            }
            ToolButton {
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
            ToolButton {
                text: qsTr("Close")
                Layout.alignment: Qt.AlignRight
                onClicked:{
                    messageDialogText=qsTr("Are you sure you want to quit")
                    var messageDlg = messageDialog.createObject(parent)
                    messageDlg.yes.connect(function(){
                        Qt.quit()
                    })
                }

            }
        }
    }
}

