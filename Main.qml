import QtQuick
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Controls 

ApplicationWindow 
{
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
                     //new_game()
                }
            }
            MenuItem 
            {
                text: qsTr("Ex&it")
                onTriggered: Qt.quit();
            }
        }
    }
    
    id: parent_win
    visible: true
    minimumHeight: 640;
    minimumWidth: 640;
        
    Grid 
    {
        id: sudokiGrid;
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
