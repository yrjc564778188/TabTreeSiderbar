#include "treeitem.h"

treeItem::treeItem()
    :QStandardItem("")
{}

treeItem::treeItem(QString text)
    :QStandardItem(text)
{

}
treeItem::treeItem(const QIcon &icon, const QString &text)
    :QStandardItem(icon, text)
{

}
