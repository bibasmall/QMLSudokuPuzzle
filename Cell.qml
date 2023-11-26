import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Dialogs 


Button 
{
    id: cell
    
    required property int count
    required property bool readOnly
    required property string val
    
    height: parent.height
    width: parent.width
    
    background: Rectangle 
    {
        id: cellBackground
        anchors.centerIn: parent        
        height: parent.height
        width: parent.width
        color: "white"
        
        Rectangle {anchors.left: parent.left; height: parent.height; width: count % 3 ? 0.5 : 3; color: "black"}
        Rectangle {anchors.right: parent.right; height: parent.height; width: (count + 1) % 9 ? 0.5 : 3; color: "black"}
        Rectangle 
        {
            anchors.bottom: parent.bottom;
            height: (Math.floor(count / 9) == 2) || Math.floor(count / 9) == 5 || Math.floor(count / 9) == 8 ? 3 : 0.5; 
            width: parent.width 
            color: "black"
        }
        Rectangle {anchors.top: parent.top; height:  Math.floor(count / 9) ? 0.5 : 3; width: parent.width; color: "black"}
    }
    TextInput 
    {
        id: txt
        enabled: !parent.readOnly; font.bold: parent.readOnly;
        text: cell.val
        validator: RegularExpressionValidator  { regularExpression: /[1-9]+/ }
        inputMask: "9"
        maximumLength: 1
        anchors.centerIn: parent
        font.pointSize: parent.height / 2
        selectByMouse : false
        
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
               
        onTextEdited:
        {
            cell.valueChanged(txt.text)
        }
        onFocusChanged: 
        {
            cursorPosition = 0
        }
    }
    onHoveredChanged: 
    {
        cellBackground.color = hovered ? "powderblue" : "white";
    }
    
    signal valueChanged(string val)
}
