#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MediaJob.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connecting button to slot
    /* ui->convertButton = the button added from the designer
     * &QPushButton::clicked = the signal the button emits when clicked
     * this = MainWindow object, which contains the slot
     * &MainWindow::onStartButtonClicked = the slot (function) that runs when the signal fires
     */
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);

    // connecting select video button to slot
    connect(ui->selectVideo, &QPushButton::clicked, this, &MainWindow::onSelectVideoClicked);

    // on conversion finished
    process = new QProcess(this);
    connect(process, &QProcess::finished, this, &MainWindow::onConversionFinished);

    // connecting stderr for live progress bar
    connect(process, &QProcess::readyReadStandardError, this, &MainWindow::onReadyReadStandardError);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSelectVideoClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Directory",
                                                    QDir::homePath() + "/Desktop");
    QFileInfo fileInfo(filePath);

    if (fileInfo.suffix().toLower() != "mp4" && fileInfo.suffix().toLower() != "")
    {
        QMessageBox::warning(this, "Error: ", "File is not a .mp4 format!");
        return;  // file not a .mp4
    } else // works, otherwise
    {
        selectedVideoPath = filePath; // holding directory until user selects Convert button
        ui->labelSelectedVideo->setText("File Selected: " + fileInfo.completeBaseName() + ".mp4"); // showing what directory the user selected in label
    }
}

void MainWindow::onStartButtonClicked()
{
    QString filePath = selectedVideoPath;

    if (filePath.isEmpty())
    {
        QMessageBox::warning(this, "Error: ", "No file selected!"); // no file selected
        return;
    } else
    {
        QString ffmpegPath = QCoreApplication::applicationDirPath() + "/ffmpeg/bin/ffmpeg.exe";
        QString outputPath = QFileDialog::getSaveFileName(this, "Select Directory", QDir::homePath() + "/Desktop/output.mp3", "MP3 Files (*.mp3)");;

        if (outputPath.isEmpty())
        {
            return;
        }

        // PROCESSING VIDEO
        // NOTE:
            // program freezes when user tries to replace existing file
            // FIX THIS
        qDebug() << "Input: " << selectedVideoPath;
        qDebug() << "Output: " << outputPath;
        QStringList args;
         args
             << "-i"
             << selectedVideoPath
             << "-vn"
             << outputPath;

        qDebug() << "ARGS Size: " << args.size();
        qDebug() << args;
        ui->convertButton->setEnabled(false);

        // progress bar
        totalDurationSeconds = getVideoDurationInSeconds(selectedVideoPath);
        ui->progressBar->setValue(0);
        ui->progressBar->setRange(0, 100);

        process->start(ffmpegPath, args);

        qDebug() << "FFmpeg path: " << ffmpegPath;
        qDebug() << "Process error: " << process->errorString();

        if (!process->waitForStarted())
        {
            QMessageBox::warning(this, "Error", "FFmpeg failed to start!");
            ui->convertButton->setEnabled(true);
            return;
        }
    }
}

double MainWindow::getVideoDurationInSeconds(const QString &inputPath)
{
    QString ffprobePath = QCoreApplication::applicationDirPath() + "/ffmpeg/bin/ffprobe.exe";
    QProcess probe;
    /* building the command line call to ffprobe
    / ffprobe -v error -show_entries format=duration -of default=noprint_wrappers=1:nokey=1
    / input.mp4 */
    QStringList probeArgs;
    probeArgs << "-v"
              << "error"
              << "-show_entries"
              << "format=duration"
              << "-of"
              << "default=noprint_wrappers=1:nokey=1"
              << inputPath;
    probe.start(ffprobePath, probeArgs);

    if (!probe.waitForStarted() || !probe.waitForFinished())
    {
        return 0.0;
    }

    QString output = QString::fromUtf8(probe.readAllStandardOutput().trimmed());
    return output.toDouble();
}

void MainWindow::onReadyReadStandardError()
{
    QString output = QString::fromUtf8(process->readAllStandardError());
    qDebug() << output;

    /* extracting live progress from FFmpeg output
    / FFmpeg format = xx:xx:xx.xx"
    / therefore, \d{2} = hours, : = separator, (\d{2}) = minutes, : = separator,
    / (\d{2}\.\d+) = seconds with decimals */
    QRegularExpression re(R"(time=(\d{2}):(\d{2}):(\d{2}\.\d+))");

    QRegularExpressionMatch match = re.match(output);

    if (match.hasMatch() && totalDurationSeconds > 0.0)
    {
        int hours = match.captured(1).toInt();
        int minutes = match.captured(2).toInt();
        double seconds = match.captured(3).toDouble();

        double currentSeconds = hours * 3600 + minutes * 60 + seconds;
        int progress = static_cast<int>((currentSeconds / totalDurationSeconds) * 100.0);

        if (progress > 100)
        {
            progress = 100;
        }
        if (progress < 0)
        {
            progress = 0;
        }
        ui->progressBar->setValue(progress);
    }
}

void MainWindow::onConversionFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->convertButton->setEnabled(true);

    if (exitStatus == QProcess::NormalExit && exitCode ==0)
    {
        ui->progressBar->setValue(100);
        QMessageBox::information(this, "Alert", "Processing Finished");
    } else
    {
        QMessageBox::warning(this, "Alert", "Processing Failed!");
    }

}
