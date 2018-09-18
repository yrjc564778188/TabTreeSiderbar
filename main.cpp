
//#include "treeviewwidget.h"

#include <QApplication>

//#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlComponent>
#include <QQuickItem>
#include <tree/TreeSearch.h>
#include <tree/treemodel.h>

int main(int argc, char *argv[])
{
    //    QApplication app(argc, argv);
    //    treeViewWidget treeWidget;
    //    treeWidget.show();


    //////////////////////////////////////////////////////////////////////

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty("TreeModel", new TreeModel);
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    /////////////////////////////////////////////////////////////////////////////
//    TreeModel *pTreeModel = new TreeModel;
//    int iRootCount = pTreeModel->rowCount();
//    for (int i = 0; i < iRootCount; ++i)
//    {
//        QModelIndex curIndex = pTreeModel->index(i, 0);
//        QString str = pTreeModel->data(curIndex, 12345).toString();
//        qDebug()<<"main parent:"<<str;
//        int nChildCount = curIndex.model()->rowCount();
//        for(int j = 0; j < nChildCount; j++)
//        {
//            QModelIndex childIndex = pTreeModel->index(j, 1, curIndex);
//            QString str = pTreeModel->data(childIndex, 12345).toString();
//            qDebug()<<"child parent:"<<str;
//        }
//    }

/////////////////////////////////////////////////////////////////////////////

    qmlRegisterType<treeModel>("component.TreeModel", 1, 0, "TreeModel");

//    qmlRegisterType<TreeModels>("component.TreeModel", 1, 0, "TreeModel");
    qmlRegisterType<TreeSearch>("component.TreeSearch", 1, 0, "TreeSearch");

    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *object = component.create();

    QObject * treeView = object->findChild<QObject *>("ditu");
    if(treeView){
//        QVariant variant = treeView->property("color");
        qDebug()<< "treeView width value is"<<treeView->property("color").toString();
    }

//    QTreeView treeview;
//    TreeSearch treeSearch;
//    QObject::connect(object, SIGNAL(search(QString, QString)),
//                     &treeSearch, SLOT(SearchItem(QString, QString)));

    ////////////////////////////////////////////////////////////////////////////////

    return app.exec();
}
