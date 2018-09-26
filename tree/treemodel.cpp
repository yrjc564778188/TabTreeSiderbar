#include "treemodel.h"

treeModel::treeModel(QObject *parent)
    :QStandardItemModel(parent)
{
    this->setHorizontalHeaderLabels(QStringList()<<QString("树形控件"));
    treeItem *fstItem = new treeItem(tr("第一级菜单1"));
    fstItem->setData(tr("第一级菜单"));

    treeItem *fstItem1 = new treeItem(tr("第二级子菜单1"));
    treeItem *fstItem2 = new treeItem(tr("第二级子菜单2"));
    treeItem *fstItem3 = new treeItem(tr("第二级子菜单3"));
    //设置checkbox风格
    fstItem1->setCheckable(true);
    fstItem1->setAutoTristate(true);

    fstItem->appendRow(fstItem1);
    fstItem->appendRow(fstItem2);
    fstItem->appendRow(fstItem3);
    treeItem *trdItem1 = new treeItem(tr("第三级子菜单1"));
    treeItem *trdItem2 = new treeItem(tr("第三级子菜单2"));
    treeItem *trdItem3 = new treeItem(tr("第三级子菜单3"));
    trdItem1->setCheckable(true);
    trdItem2->setCheckable(true);
    trdItem3->setCheckable(true);
    fstItem1->appendRow(trdItem1);
    fstItem1->appendRow(trdItem2);
    fstItem1->appendRow(trdItem3);
    treeItem *trdItem4 = new treeItem(tr("第三级子菜单1"));
    treeItem *trdItem5 = new treeItem(tr("第三级子菜单2"));
    treeItem *trdItem6 = new treeItem(tr("第三级子菜单3"));
    fstItem3->appendRow(trdItem4);
    fstItem3->appendRow(trdItem5);
    fstItem3->appendRow(trdItem6);

    treeItem *secItem = new treeItem(tr("第一级菜单2"));
    treeItem *secItem1 = new treeItem(tr("第二级子菜单1"));
    treeItem *secItem2 = new treeItem(tr("第二级子菜单2"));
    treeItem *secItem3 = new treeItem(tr("第二级子菜单3"));
    secItem->appendRow(secItem1);
    secItem->appendRow(secItem2);
    secItem->appendRow(secItem3);

    this->appendRow(fstItem);
    this->appendRow(secItem);

    //关联项目属性改变的信号和槽
    connect ( this ,&QStandardItemModel::itemChanged , this ,&treeModel::treeItemChanged );
//    connect(this,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(treeItemChanged(QStandardItem*)));

}

//QModelIndex treeModel::index(int row, int column, const QModelIndex &parent) const
//{
//    if(!hasIndex(row, column, parent))
//    {
//        return QModelIndex();
//    }

//    treeModel *parentItem;
//    if(!parent.isValid())
//    {
//        parentItem = m_rootItem;
//    }
//    else
//    {
//        parentItem = static_cast<treeModel*>(parent.internalPointer());
//    }

//    treeModel *childItem = parentItem->child(row);
//    if(childItem)
//    {
//        return createIndex(row, column, childItem);
//    }
//    else
//    {
//        return QModelIndex();
//    }
//}


//根据子节点的改变，更改父节点的选择情况
void treeModel::treeItem_CheckChildChanged(QStandardItem * item)
{

    if(nullptr == item)
        return;
    Qt::CheckState siblingState = checkSibling(item);
    QStandardItem * parentItem = item->parent();
    if(nullptr == parentItem)
        return;
    if(Qt::PartiallyChecked == siblingState)
    {
        if(parentItem->isCheckable() && parentItem->isAutoTristate())
            parentItem->setCheckState(Qt::PartiallyChecked);
    }
    else if(Qt::Checked == siblingState)
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Checked);
    }
    else
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Unchecked);
    }
    treeItem_CheckChildChanged(parentItem);

}

///
/// \brief 递归设置所有的子项目为全选或全不选状态
/// \param item 当前项目
/// \param check true时为全选，false时全不选
///
void treeModel::treeItem_checkAllChild(QStandardItem * item, bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}
void treeModel::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}

///
/// \brief 测量兄弟节点的情况，如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
/// \param item
/// \return 如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
///
Qt::CheckState treeModel::checkSibling(QStandardItem * item)
{
    //先通过父节点获取兄弟节点
    QStandardItem * parent = item->parent();
    if(nullptr == parent)
        return item->checkState();
    int brotherCount = parent->rowCount();
    int checkedCount(0),unCheckedCount(0);
    Qt::CheckState state;
    for(int i=0;i<brotherCount;++i)
    {
        QStandardItem* siblingItem = parent->child(i);
        state = siblingItem->checkState();
        if(Qt::PartiallyChecked == state)
            return Qt::PartiallyChecked;
        else if(Qt::Unchecked == state)
            ++unCheckedCount;
        else
            ++checkedCount;
        if(checkedCount>0 && unCheckedCount>0)
            return Qt::PartiallyChecked;
    }
    if(unCheckedCount>0)
        return Qt::Unchecked;
    return Qt::Checked;
}

void treeModel::treeItemClicked(QModelIndex index, int checkedState)
{
    QStandardItem *item = QStandardItemModel::itemFromIndex(index);
    QStandardItem * parent = item->parent();
    QModelIndex parenttest;
    if(parent)
    {
        parenttest = parent->index();
        parent->setCheckable(true);
    }

    QModelIndex test = item->index();
    if(item)
    {
        item->setCheckable(true);
        item->setCheckState(static_cast<Qt::CheckState>(checkedState));
        emit itemChanged(item);
    }

    //treeItemChanged(item);
}

Qt::CheckState treeModel::getState(QModelIndex index)
{
    QStandardItem *item = QStandardItemModel::itemFromIndex(index);
    Qt::CheckState state = Qt::Unchecked;
    if(item)
    {
        QVariant itemText;
        itemText = item->data();
        state = item->checkState();
    }
    return state;
}

void treeModel::treeItemChanged ( QStandardItem * item )
{
    if ( item == nullptr )
        return ;
    if ( item -> isCheckable ())
    {
        //如果条目是存在复选框的，那么就进行下面的操作
        Qt :: CheckState state = item -> checkState (); //获取当前的选择状态
        if ( item -> isAutoTristate ())
        {
             //如果条目是三态的，说明可以对子目录进行全选和全不选的设置
            if ( state != Qt :: PartiallyChecked )
            {
                //当前是选中状态，需要对其子项目进行全选
                treeItem_checkAllChild ( item , state == Qt::Checked ? true : false );
            }
        }
        else
        {
            //说明是两态的，两态会对父级的三态有影响
            //判断兄弟节点的情况
            treeItem_CheckChildChanged ( item );
        }
    }
}

