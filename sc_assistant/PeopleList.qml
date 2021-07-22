import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import Sc_assistant.BackEnd 1.0


Item{
    id:peopleList

    ScrollView {
        id:scroll
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        height: stack.height
        width: stack.width

        ListView {
            id:list
            model: backend.getPeopleList()

            delegate: ItemDelegate {
                id:listdelegate
                width: parent.width
                RowLayout{
                    width: parent.width
                    id:row
                    Switch{
                        id:cb
                        Layout.alignment: Layout.Left
                        checked: modelData.state
                        onToggled: {
                            backend.visitorSetFinishedState(index,cb.checked)
                        }
                    }
                    Text {
                        Layout.alignment:  Layout.Right
                        Layout.fillWidth: true
                        text: modelData.name
                        font.pointSize: 12
                        color: "#ffffff"

                    }
                }



                onClicked: {
                    list.currentIndex = index
                    visitorIndex = index
                    backend.loadVisitor(visitorIndex)
                    stack.pop()
                    stack.push(editVisitor)
                    menuBackIcon.state = "back"
                    addButton.visible = false
                    finisedSate = cb.checked
                }
            }

        }
    }

}
