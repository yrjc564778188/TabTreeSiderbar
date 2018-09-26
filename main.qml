import QtQuick 2.9
//import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQml.Models 2.3

import component.TreeModel 1.0
import component.TreeSearch 1.0
ApplicationWindow {
    id: appwindow
    visible: true
    width:  280
    height: 640
    title: qsTr("TabTreeSiderbar")




    TreeModel{
        id: treeModel
//        objectName: "treemode"
    }

    TreeSearch{
        id: treeSearch
        onExpandModel:{
            treeView.expand(indexSearched)
//            console.log("treeSearch");
        }
    }

    TabWidget {
        id: tabs
        objectName: "tabwidget"
        anchors.fill: parent
        width: 281
//        height: 480

        Rectangle {
            property string title: "警力"
            anchors.fill: parent
            color: "#e3e3e3"

            Rectangle {
                anchors.fill: parent; anchors.margins: 20
                color: "#ff7f7f"
                Text {
                    width: parent.width - 20
                    anchors.centerIn: parent; horizontalAlignment: Qt.AlignHCenter
                    text: "警力部署图……"
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                }
            }
        }

        Rectangle {
            property string title: "设备"
            anchors.fill: parent
            color: "#e3e3e3"

            TextField{
                id: textSearch
                placeholderText: qsTr("请输入关键字查询")
                //anchors.topMargin: 40
                width: parent.width - 8
                anchors.horizontalCenter: parent.horizontalCenter

                onAccepted: {

                        console.log(text)
                        treeView.search(text)
                }
            }


            Row {
                id: row
                anchors.top: parent.top //- TextField.height
                anchors.topMargin: 12*3
                //anchors.horizontalCenter: parent.horizontalCenter

                ExclusiveGroup {
                    id: eg
                }

                Repeater {
                    model: [ "摄像头", "wifi", "基站", "卡口"]

                    Label {
                        text: modelData
                        padding: 8
//                        exclusiveGroup: eg
//                        checkable: true
//                        checked: index === 1

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                textSearch.text = modelData
//                                textSearch.search(text)

                            }
                        }

//                        onClicked: {
//                            treeView.selectionMode = index
//                            textSearch.text = modelData
//                            textSearch.search(text)
//                        }
                    }
                }
            }

//            ItemSelectionModel {
//                id: sel
//                model: treeModel
//            }

            TreeView {
                id: treeView
                anchors.fill: parent
                anchors.topMargin: 12*6
                model: treeModel
                signal search(string keyWord);
                //selection: sel
                headerVisible: false
                width: parent.width - 20
                alternatingRowColors: true //背景交替
                backgroundVisible: true  //背景
                selection: ItemSelectionModel {
                    model: treeModel

                }
//                selectionMode: SelectionMode.NoSelection // 多选
//                Component.onCompleted: {
//                    //model = treeModel.model();
//                    model = treeModel;
//                    print(model);
//                }

                itemDelegate: CheckBox {
                    id: checkID
                    activeFocusOnPress: false
                    //color: styleData.textColor
                    //elide: styleData.elideMode
//                  partiallyCheckedEnabled: true
                    checkedState: treeModel.getState(styleData.index)
                    text: styleData.value
//                    onTextChanged: {
//                        print(text)
//                    }
                    onClicked: {
//                        print(checkedState)
                        treeModel.treeItemClicked(styleData.index, checkedState)
                    }
                }


                TableViewColumn {
                    horizontalAlignment: Qt.AlignLeft;
                    width: 150
                    title: "2"
                    role: "display"
                }

//                onClicked: {
////                    console.log("onClicked", index)
////                    console.log("isExpanded", isExpanded(index))
//                    //emit: treeView.expand(index)
//                    treeModel.treeItemClicked(index)
//                }


            }

            Connections{
                target: treeView
                onSearch:{
                    console.log(keyWord)
                    treeSearch.SearchItem(treeModel, keyWord)
                }
            }
        }

        Rectangle {
            property string title: "地图"
            anchors.fill: parent; color: "#e3e3e3"
            objectName: "ditu"
            Rectangle {
                anchors.fill: parent; anchors.margins: 20
                color: "#7f7fff"
                Text {
                    width: parent.width - 20
                    anchors.centerIn: parent; horizontalAlignment: Qt.AlignHCenter
                    text: "地图展示……"
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                }
            }
        }
    }

}



