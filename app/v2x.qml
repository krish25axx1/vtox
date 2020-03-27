
import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import AGL.Demo.Controls 1.0

ApplicationWindow {
    id: root

    width: container.width * container.scale
    height: container.height * container.scale

    Item {
        id: container
        anchors.centerIn: parent
        width: 1080
        height: 1487
        scale: screenInfo.scale_factor()

        TabBar {
            id: bar
            width: parent.width
            contentHeight: 160

            TabImageButton {
                icon: ""
                text: "V2X Infra Alerts"
                font.pixelSize: 50
            }

          
        }

        StackLayout {
            anchors.top: bar.bottom
            width: parent.width
            height: parent.height - bar.height
            currentIndex: bar.currentIndex
            NotificationPage {
                id: V2X Infra Alerts
            }
           
        }

        Keyboard {
            id: keyboard
            target: activeFocusControl
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }
    }
}
