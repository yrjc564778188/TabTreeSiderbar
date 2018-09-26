#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "treeitem.h"

#include <QStandardItemModel>



class treeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    treeModel(QObject *parent = NULL);

private:
    //QList<treeItem*> m_treeRoot;//树的根节点
public slots:
    void treeItemClicked(QModelIndex index, int checkedState);
    Qt::CheckState getState(QModelIndex index);
private slots:

    void treeItemChanged(QStandardItem * item);

    void treeItem_checkAllChild(QStandardItem * item,bool check = true);
    void treeItem_checkAllChild_recursion(QStandardItem * item,bool check = true);
    Qt::CheckState checkSibling(QStandardItem * item);
    void treeItem_CheckChildChanged(QStandardItem * item);

};

#endif // TREEMODEL_H
