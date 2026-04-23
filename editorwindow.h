#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QDialog>

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

private:
    Ui::EditorWindow *ui;
};

#endif // EDITORWINDOW_H
