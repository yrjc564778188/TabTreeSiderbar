#include "treeviewwidget.h"

#include <ui_treeView.h>

#include <tree/treemodel.h>

treeViewWidget::treeViewWidget(QWidget* parent)
    :QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    treeModel *pTreeModel = new treeModel(this);


    ui->treeView->setModel(pTreeModel);
}
