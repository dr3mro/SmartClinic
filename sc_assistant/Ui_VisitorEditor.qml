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
    property alias visitorAge : age.text;
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


            TextInputWithLabel { // patient ID
                id:visitorID
                label: qsTr("ID")
                placeholderText: qsTr("Visitor ID")
                validator: RegExpValidator { regExp: /[0-9]{1,7}/ }
            }


            TextInputWithLabel { // patient Name
                id:name
                label: qsTr("Name")
                placeholderText: qsTr("Visitor Name")
            }


            TextInputWithLabel{
                id:age
                label: qsTr("Age")
                placeholderText: qsTr("Visitor Age")
                validator: RegExpValidator { regExp: /[0-9]{1,2}/ }
            }

            ComboBoxWithTextField {
                id: sex
                label: qsTr("Sex")
                model: [ qsTr("Male"),  qsTr("Female")]
            }



            ComboBoxWithTextField {
                id: marital
                label: qsTr("Marital")
                model: [ qsTr("Single"),qsTr("Married"),qsTr("Widdowed"),qsTr("Devorced")]
            }


            TextInputWithLabel{
                id:residence
                label : qsTr("Residence")
                placeholderText: qsTr("Residence")
            }

            TextInputWithLabel{
                id:placeofbirth
                label : qsTr("Place of birth")
                placeholderText: qsTr("Place of birth")
            }

            TextInputWithLabel{
                id:job
                label : qsTr("Job")
                placeholderText: qsTr("Job")
            }

            TextInputWithLabel{
                id:mobile
                label : qsTr("Tel")
                placeholderText: qsTr("Telephone")
            }

            ComboBoxWithTextField{
                width: parent.width
                label: qsTr("Visit Type")
                id:visitType
                model: [ qsTr("New"),qsTr("follow1"),qsTr("follow2"),qsTr("follow3"),qsTr("follow4"),qsTr("free")]
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
