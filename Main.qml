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
            title: "Game"
            MenuItem 
            {
                id: newMenu
                text: "New"
                onTriggered: sudokuModel.onNewGame()
            }
            MenuItem 
            {
                text: "Check"
                onTriggered: sudokuModel.onCheck();
            }
            MenuItem 
            {
                id: solveMenu
                text: "Solve"
                onTriggered: 
                {
                    sudokuModel.onSolve(); 
                    solveMenu.enabled = false
                }
            }
            MenuItem 
            {
                text: "Exit"
                onTriggered: Qt.quit();
            }
            
            Connections 
            {
                target: newMenu
                function onTriggered()
                {
                    solveMenu.enabled = true
                }
                
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
            Cell { id: cell; val : Value; readOnly: val != ""; count : Count; }
            
             Connections 
             {
                 target: cell
                 function onValueChanged(val)
                 {
                     console.log(val);
                     console.log(cell.count);
                     model.Value = val;
                 }
             }
             Connections 
             {
                 target: sudokuModel
                 function onBoardChangedFromInside(val)
                 {
                     grid.update()
                 }
             }
        }
    }
       
}
