#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QProcess>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class JobType
{
  None,
  Convert,
  Trim
};

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
    void onSelectVideoToEdit();
    void onReadyReadStandardError();
    void onConversionFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onTrimButtonClicked();

private:
    QProcess *process;
    Ui::MainWindow *ui;
    QString selectedVideoPath;
    double totalDurationSeconds = 0.0;

    double getVideoDurationInSeconds(const QString &inputPath);
    QString secondsToTime(int totalSeconds);

    JobType currentJob = JobType::None;

};
#endif // MAINWINDOW_H
