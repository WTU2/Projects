#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDockWidget>

namespace Ui {
class EditWindow;
}

class EditWindow : public QDockWidget
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = nllptr);
    ~EditWindow();
private:
    Ui::EditWindow *ui;
};

#endif // EDITWINDOW_H
