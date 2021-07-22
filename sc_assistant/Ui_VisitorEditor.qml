import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.0

Item {
    property alias save_btn: btn_save
    property alias del_btn: btn_del
    property alias visitorName : name.text
    property alias visitorID : visitorID.text;
    property alias visitorAge : age.value;
    property alias visitorSex : sex.currentIndex;
    property alias visitorMarital : marital.currentIndex;
    property alias visitorResidence : residence.text
    property alias visitorPlaceofbirth : placeofbirth.text
    property alias visitorTel : mobile.text;
    property alias visitorVisitType : visitType.currentIndex;
    property alias visitorJob : job.text

    Flickable{
        id:flickable
        anchors.fill: parent
        anchors.margins: 20
        anchors.bottomMargin: inputRect.visible ? inputRect.height : anchors.margins
        contentHeight: column.implicitHeight
        flickableDirection: Flickable.VerticalFlick
        ColumnLayout{
            id:column
            width: parent.width
            RowLayout{
                width: parent.width
                Label{
                    text: qsTr("ID")

                }
                TextField{
                    id:visitorID
                    placeholderText: qsTr("Visitor ID")
                    Layout.fillWidth: true
                    selectByMouse: true
                }

            }


            RowLayout{
                width: parent.width
                Label{
                    text: qsTr("Name")
                }
                TextField{
                    id:name
                    placeholderText: qsTr("Visitor Name")
                    Layout.fillWidth: true
                    selectByMouse: true

                }

            }


            RowLayout{
                width: parent.width
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
                width: parent.width
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
                width: parent.width
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
                width: parent.width
                Label{
                    text: qsTr("Residence")

                }
                TextField{
                    id:residence
                    placeholderText: qsTr("Residence")
                    Layout.fillWidth: true
                    selectByMouse: true

                }

            }



            RowLayout{
                width: parent.width
                Label{
                    text: qsTr("Place of birth")

                }
                TextField{
                    id:placeofbirth
                    placeholderText: qsTr("Place of birth")
                    Layout.fillWidth: true
                    selectByMouse: true

                }

            }
            RowLayout{
                width: parent.width
                Label{
                    text: qsTr("Job")

                }
                TextField{
                    id:job
                    placeholderText: qsTr("Job")
                    Layout.fillWidth: true
                    selectByMouse: true
                }

            }


            RowLayout{
                width: parent.width
                Label{
                    text: qsTr("Tel")
                }
                TextField{
                    id:mobile
                    placeholderText: qsTr("Telephone")
                    Layout.fillWidth: true
                    selectByMouse: true
                }

            }


            RowLayout{
                width: parent.width
                Label{
                    text: qsTr("Visit Type")

                }
                ComboBox{
                    id:visitType
                    model: [ qsTr("New"),qsTr("follow1"),qsTr("follow2"),qsTr("follow3"),qsTr("follow4"),qsTr("free")]
                    Layout.fillWidth: true
                }

            }



            RowLayout{
                width: parent.width
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Button{
                    id:btn_save
                    text:qsTr("Save")
                    Layout.alignment: Qt.AlignLeft
                    Material.background: "Green"
                }


                Button{
                    id:btn_del
                    text:qsTr("Delete")
                    Layout.alignment: Qt.AlignHCenter
                    Material.background: "red"
                    onClicked: {
                        messageDialogText=qsTr("Are you sure you want to delete this visitor")
                        var messageDlg = messageDialog.createObject(parent)
                        messageDlg.yes.connect(function(){
                            backend.delVisitor(visitorIndex)
                            stack.pop()
                            stack.push(peopleList)
                            addButton.visible = true
                            menuBackIcon.state = "menu"
                        })

                    }
                }

                Button{
                    id:btn_back
                    text:qsTr("Back")
                    Layout.alignment: Qt.AlignRight
                    Material.background: "steelblue"
                    onClicked: {
                        addButton.visible = true
                        menuBackIcon.state = "menu"
                        stack.pop()
                        stack.push(peopleList)
                    }
                }
            }
            Rectangle{
                id:inputRect
                height: stack.height * 0.3
                visible: Qt.inputMethod.visible
            }
        }
    }
}
