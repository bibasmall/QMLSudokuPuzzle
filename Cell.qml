import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Dialogs 

Button 
{
    id: cell
    
    property int count: 2
    property bool readOnly: false
    property int val: 0
    
    height: parent.height/9
    width: parent.width/9
    
    background: Rectangle 
    {
        id: cellBackground
        anchors.centerIn: parent;        
        height: parent.height
        width: parent.width
        color: "white"
        
        Rectangle {anchors.left: parent.left; height: parent.height; width: 1; color: "black"}
        Rectangle {anchors.right: parent.right; height: parent.height; width: 1; color: "black"}
        Rectangle {anchors.right: parent.bottom; height: 1; width: parent.width; color: "black"}
        Rectangle {anchors.right: parent.top; height: 1; width: parent.width; color: "black"}
    }
    TextInput 
    {
        id: txt
        enabled: !parent.readOnly; font.bold: parent.readOnly
        text: cell.val > 0 ? val : " "
        validator: RegularExpressionValidator  { regularExpression: /[1-9]+/ }
        inputMask: "9"
        anchors.fill: parent
        font.pointSize: parent.height/2
        verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter
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
