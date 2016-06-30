import QtQuick 1.0

 Rectangle {
     id: simplebutton
     color: "grey"
     width: 150; height: 75


ListModel {
    id: fruitModel

    ListElement {
        name: "Apple"
        cost: 2.45
    }
    ListElement {
        name: "Orange"
        cost: 3.25
    }
    ListElement {
        name: "Banana"
        cost: 1.95
    }
}
 TableView {
     anchors.fill: parent
     model: fruitModel
     delegate: Row {
         Text { text: "Fruit: " + name }
         Text { text: "Cost: $" + cost }
     }
 }
 }