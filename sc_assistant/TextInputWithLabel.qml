import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.0

RowLayout{
    property alias text: textField.text
    property alias placeholderText: textField.placeholderText
    property alias validator: textField.validator
    property alias label: label.text

    layoutDirection: Qt.RightToLeft

    Label{
        id:label
    }
    TextField{
        id:textField
        Layout.fillWidth: true
        selectByMouse: true
        horizontalAlignment: Text.AlignHCenter
    }

}
