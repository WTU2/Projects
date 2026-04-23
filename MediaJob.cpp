#include "MediaJob.h"
#include <QDebug>
#include <QThread>
#include <QProcess>

MediaJob::MediaJob(const QString& inputFile, const QString& outputFile) : inputPath(inputFile), outputPath(outputFile), progress_(0)
{
}

void MediaJob::start()
{
    // trying to see if the button works
    // extracting from input file, we get the mp3 file and direct it as output file
    // manually updating the current progress of the job, from 0 to 100
    // TO DO:
        // update progress respective to the process of the conversion of the .mp4 file    
    for (int i = 0; i <= 100; i++)
    {
        progress_ = i;

        QThread::msleep(10); // sleep to simulate work
    }    
}

int MediaJob::progress()
{
    // simply returns the current value of progress_, a getter function basically
    return progress_;
}
