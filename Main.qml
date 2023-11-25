import QtQuick
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Controls 


ApplicationWindow 
{ 
    id: wnd
    visible: true
    minimumHeight: 640;
    minimumWidth: 640;
    
    menuBar: MenuBar 
    {
        Menu 
        {
            title: qsTr("&Game")
            MenuItem 
            {
                text: qsTr("&New")
                onTriggered: sudokuModel.onNewGame()
            }
            MenuItem 
            {
                text: qsTr("Ex&it")
                onTriggered: Qt.quit();
            }
        }
    }
    
    GridView 
    {
        id: grid
        anchors.fill: parent
        focus: true
        height: parent.height; width: parent.width;
        model: sudokuModel
        
        cellWidth: grid.width/9 
        cellHeight: grid.height/9
        
        delegate: Column
        {
            width: grid.cellWidth
            height: grid.cellHeight
            Cell { val : Value}
        }
    }
       
}
