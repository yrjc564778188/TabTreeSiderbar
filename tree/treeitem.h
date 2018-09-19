#ifndef TREEITEM_H
#define TREEITEM_H

#include <QStandardItemModel>


class treeItem : public QStandardItem
{
public:
    treeItem();
    treeItem(const QIcon &icon, const QString &text);
    treeItem(QString text);


};

#endif // TREEITEM_H
