#include "uploadthread.h"
#include <QProcess>
#include <QString>
#include <QDebug>

extern QString globalBatPath;
extern QString globalPicSavePath;

UploadThread::UploadThread(QObject *parent = Q_NULLPTR)
    :QThread(parent)
{

}

void UploadThread::run()
{
    QProcess process;
    qDebug()<<"Thread running........."<<endl;
//    process.start("cmd.exe");
//    process.waitForFinished();

//    QString writeText = globalBatPath + "\n";
//    process.write(writeText.toStdString().c_str());
//    process.waitForFinished(-1);
    process.setWorkingDirectory(globalPicSavePath);
    process.start("cmd.exe", QStringList() << "/c" << globalBatPath);
    process.waitForFinished(-1);
    qDebug() << process.readAllStandardOutput()<<endl;
    qDebug() << "ok------"<<endl;
    qDebug()<<globalBatPath<<endl;

//    system(globalBatPath.toStdString().c_str());
}
