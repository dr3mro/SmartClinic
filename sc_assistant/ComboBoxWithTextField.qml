import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.0

RowLayout{
    property alias model: comboBox.model
    property alias label: label.text
    property alias currentIndex: comboBox.currentIndex

    layoutDirection: Qt.RightToLeft

    Label{
        id:label
        Layout.fillWidth: true
    }
    ComboBox{
        id: comboBox
        delegate: ItemDelegate {
            id: itemDelegate
            width: parent.width
            text: comboBox.textRole ? (Array.isArray(comboBox.model) ? modelData[comboBox.textRole] : model[comboBox.textRole]) : modelData
            font.weight: comboBox.currentIndex === index ? Font.DemiBold : Font.Normal
            highlighted: comboBox.highlightedIndex === index
            hoverEnabled: comboBox.hoverEnabled
            contentItem: Label {
                text: itemDelegate.text
                font: itemDelegate.font
                verticalAlignment:  Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
            }
        }
    }
}
