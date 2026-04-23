#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QProcess>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // slots for buttons
private slots:
    void onStartButtonClicked();
    void onSelectVideoClicked();
    void onReadyReadStandardError();
    void onConversionFinished(int exitCode, QProcess::ExitStatus exitStatus);


private:
    QProcess *process;
    Ui::MainWindow *ui;
    QString selectedVideoPath;
    double totalDurationSeconds = 0.0;
    double getVideoDurationInSeconds(const QString &inputPath);

};
#endif // MAINWINDOW_H
