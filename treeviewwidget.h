#ifndef TREEVIEWWIDGET_H
#define TREEVIEWWIDGET_H
#include <QWidget>

namespace Ui {
class Form;

}
class treeViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit treeViewWidget(QWidget* parent = NULL);

private:
    Ui::Form *ui;
};

#endif // TREEVIEWWIDGET_H
