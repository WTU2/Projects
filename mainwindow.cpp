#include "mainwindow.h"
#include "./ui_mainwindow.h"
// #include "MediaJob.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>
#include <QAction>

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

    // editing video
    connect(ui->selectVideoToEdit, &QPushButton::clicked, this, &MainWindow::onSelectVideoToEdit);
    connect(ui->trimButton, &QPushButton::clicked, this, &MainWindow::onTrimButtonClicked);
    connect(ui->startSlider, &QSlider::valueChanged, this, [this](int value) { // start slider
        {
            if (value >= ui->endSlider->value())
            {
                ui->startSlider->setValue(ui->endSlider->value() - 1);
                return;
            }
        }
        ui->labelStartTime->setText(" " + secondsToTime(value));
    });

    connect(ui->endSlider, &QSlider::valueChanged, this, [this](int value) // end slider
        {
            if (value <= ui->startSlider->value())
            {
                ui->endSlider->setValue(ui->startSlider->value() + 1);
                return;
            }
        ui->labelEndTime->setText(" " + secondsToTime(value));
    });

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

// editing
void MainWindow::onSelectVideoToEdit()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Directory",
                                                    QDir::homePath() + "/Desktop");
    QFileInfo fileInfo(filePath);

    if (filePath.isEmpty())
    {
        return;
    }
    QString ext = fileInfo.suffix().toLower();
    bool valid = (ext == "mp4" || ext == "mp3");

    if (!valid)
    {
        QMessageBox::warning(this, "Error: ", "File is not a .mp4 or .mp3 format!");
        return;  // file not a .mp4 or .mp3
    } else // works, otherwise
    {
        if (!filePath.isEmpty())
        {
            selectedVideoPath = filePath; // holding directory until user selects Convert button

            totalDurationSeconds = getVideoDurationInSeconds(selectedVideoPath);
            int duration = static_cast<int>(totalDurationSeconds);

            ui->startSlider->setRange(0, duration);
            ui->endSlider->setRange(0, duration);

            ui->startSlider->setValue(0);
            ui->endSlider->setValue(duration);

            ui->labelStartTime->setText(" " + secondsToTime(0));
            ui->labelEndTime->setText(" " + secondsToTime(duration));

            ui->videoFileName->setText("File Selected: " + fileInfo.fileName());
        }
        else
        {
            return;
        }
    }
}

void MainWindow::onTrimButtonClicked()
{
    QString filePath = selectedVideoPath;

    QFileInfo fileInfo(filePath);

    if (filePath.isEmpty())
    {
        QMessageBox::warning(this, "Error: ", "No file selected!");
        return;
    } else
    {

        QString outputPath = QFileDialog::getSaveFileName(this, "Select Directory", QDir::homePath() + "/Desktop/" + fileInfo.fileName());
        QString ffmpegPath = QCoreApplication::applicationDirPath() + "/ffmpeg/bin/ffmpeg.exe";

        if (outputPath.isEmpty())
        {
            return;
        }

        int startSeconds = ui->startSlider->value();
        int endSeconds = ui->endSlider->value();

        QString startTime = secondsToTime(startSeconds);
        QString endTime = secondsToTime(endSeconds);

        if (startSeconds >= endSeconds)
        {
            QMessageBox::warning(this, "Error", "Start time must be before end time");
            return;
        }

        qDebug() << "Duration: " << totalDurationSeconds;
        qDebug() << "End slider max: " << ui->endSlider->maximum();

        qDebug() << "Input EDIT: " << selectedVideoPath;
        qDebug() << "Output EDIT: " << outputPath;
        QStringList args;
        args << "-y"
             << "-ss" << startTime
             << "-to" << endTime
             << "-i" << selectedVideoPath
             << "-c" << "copy"
             << outputPath;

        ui->trimButton->setEnabled(false);
        process->start(ffmpegPath, args);

        if (!process->waitForStarted())
        {
            QMessageBox::warning(this, "Error", "FFmpeg failed to start!");
            ui->trimButton->setEnabled(true);
            return;
        }
        currentJob = JobType::Trim;
    }
}

/* ------------------------------------------------------------------------------ */
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
        if (!filePath.isEmpty())
        {
            selectedVideoPath = filePath; // holding directory until user selects Convert button
            ui->labelSelectedVideo->setText("File Selected: " + fileInfo.completeBaseName() + ".mp4"); // showing what directory the user selected in label
        }
        else
        {
            return;
        }
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
        ui->selectVideo->setEnabled(false);
        qDebug() << "Input: " << selectedVideoPath;
        qDebug() << "Output: " << outputPath;
        QStringList args;
         args
            << "-y"
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
        currentJob = JobType::Convert;
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
    ui->selectVideo->setEnabled(true);
    ui->convertButton->setEnabled(true);
    ui->trimButton->setEnabled(true);
    ui->labelSelectedVideo->setText("");
    selectedVideoPath.clear();

    if (exitStatus == QProcess::NormalExit && exitCode ==0)
    {
        if (currentJob == JobType::Convert)
        {
            ui->progressBar->setValue(100);
            QMessageBox::information(this, "Alert", "Processing Finished");
        }
        else if (currentJob == JobType::Trim)
        {
            QMessageBox::information(this, "Alert", "Trim Finished");
        }
    } else
    {
        QMessageBox::warning(this, "Alert", "Processing Failed!");
    }
    currentJob = JobType::None;
}

// helper function
QString MainWindow::secondsToTime(int totalSeconds)
{
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    return QString("%1:%2:%3")
        .arg(hours, 2, 10, QChar('0'))
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));
}
