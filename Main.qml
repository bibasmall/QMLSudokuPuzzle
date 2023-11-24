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
                onTriggered: 
                {
                     sudokuCore.onNewGame()
                }
            }
            MenuItem 
            {
                text: qsTr("Ex&it")
                onTriggered: Qt.quit();
            }
        }
    }
        
    Grid 
    {
        id: grid;
        anchors.fill: parent;
        height: parent.height; width: parent.width;
        focus: true
        
        columns: 9;
        Cell{count: 0} Cell{count: 1} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}
        Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}
        Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}
        Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}
        Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}
        Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}
        Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}
        Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}
        Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{} Cell{}  
    }
}
