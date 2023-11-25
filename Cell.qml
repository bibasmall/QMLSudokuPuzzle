import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Dialogs 


Button 
{
    id: cell
    
    property int count
    property bool readOnly: false
    property string val
    
    height: parent.height
    width: parent.width
    
    background: Rectangle 
    {
        id: cellBackground
        anchors.centerIn: parent;        
        height: parent.height
        width: parent.width
        color: "white"
        
        Rectangle {anchors.left: parent.left; height: parent.height; width: 1; color: "black"}
        Rectangle {anchors.right: parent.right; height: parent.height; width: 1; color: "black"}
        Rectangle {anchors.bottom: parent.bottom; height: 1; width: parent.width; color: "black"}
        Rectangle {anchors.top: parent.top; height: 1; width: parent.width; color: "black"}
    }
    TextInput 
    {
        id: txt
        enabled: !parent.readOnly; font.bold: parent.readOnly
        text: cell.val
        validator: RegularExpressionValidator  { regularExpression: /[1-9]+/ }
        inputMask: "9"
        anchors.centerIn: parent
        font.pointSize: parent.height / 2
        selectByMouse : false
        
        onTextEdited:
        {
            //todo
        }
    }
    onHoveredChanged: 
    {
        cellBackground.color = hovered ? "powderblue" : "white";
    }
}
