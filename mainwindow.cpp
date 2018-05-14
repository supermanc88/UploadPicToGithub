#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
//#include <QProcess>
#include <QString>
//#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QFile>

#include "uploadthread.h"

#include <QMessageBox>
#include <QTextCodec>


QString globalBatPath;
QString globalPicSavePath;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QObject::connect(this->ui->getClipboardBitmap, SIGNAL(clicked(bool)), this, SLOT(GetPicFromCurrentClipBoard());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetPicFromCurrentClipBoard()
{
    this->ui->label->setText("1111111111111111111");
}


void MainWindow::on_getClipboardBitmap_clicked()
{
    this->ui->label->setText("uploading...");
    QClipboard * clipBoard = QApplication::clipboard();
    QPixmap pixmap = clipBoard->pixmap();
    QString picPath("");
    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();
    QString dateTimeFormat = "yyyyMMddHHmmss";
    dateTimeFormat = dateTime.toString("yyyyMMddHHmmss");

    QString picSaveName = this->ui->picSaveName->text();

    if(picSaveName == "")
    {
        picPath = this->picSavePath + dateTimeFormat + ".png";
    }
    else
    {
        picPath = this->picSavePath + picSaveName + ".png";
    }

    qDebug()<<picPath;
    pixmap.save(picPath);


    /********************获取github项目下图片保存路径*********************/
    QStringList strList = picPath.split('\\');
    int index = 0;
    for(int i=0; i<strList.size(); i++)
    {
        if(strList[i] == this->projectName)
        {
            index = i;
            break;
        }
    }
    QString gitPicPath = "\\";
    for(int i=index+1; i<strList.size(); i++)
    {
        if(i == strList.size() - 1)
        {
            gitPicPath += strList[i];
        }
        else
        {
            gitPicPath += strList[i] + "\\";
        }

    }
    qDebug()<< "gitPicPath" <<gitPicPath<<endl;
    /********************获取github项目下图片保存路径*********************/

    //清空剪切板
    clipBoard->clear();



    /*********************************************
     * 完成上传功能，但是卡顿严重
     *********************************************/
    /***
     * 改用调用批处理
     */
    //释放批处理文件到图片存放目录
    /*
        @echo off

        git add %1
        git commit -m "add a pic"
        git push
    */
    QString batContent1 = QString("@echo off\r\ngit add \"%1\"\r\ngit commit -m \"add a pic\"\r\ngit push\r\n").arg(picPath);
    QString batContent = QString::fromLatin1(batContent1.toStdString().c_str());
    QString batPath = this->picSavePath + "upload.bat";
    globalPicSavePath = this->picSavePath;

    //QTextCodec::setCodecForCStrings(codec);

    QFile batFile(batPath);
//    if(!batFile.exists())
//    {
    if(!batFile.open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开失败";
    }
    batFile.write(batContent.toStdString().c_str());
    batFile.close();
//    }


    //调用批处理文件上传该图片
    //创建线程去处理
//    QProcess process;
    QString writeText = batPath;
    globalBatPath = batPath;
//    process.start("cmd.exe", QStringList()<<"/c"<<batPath);
//    process.waitForFinished();
//    qDebug() << process.readAllStandardOutput()<<endl;

//   system(writeText.toStdString().c_str());
    UploadThread * upThread = new UploadThread(this);
    connect(upThread, SIGNAL(finished()), this, SLOT(uploadComplete()));
    upThread->start();
    /****************************暂时不使用上传***************************
    QProcess process;
    process.start("cmd");
    process.waitForStarted();

    QString writeText = "cd " + this->picSavePath + "\n";
    qDebug()<< writeText<<endl;


    process.write(writeText.toStdString().c_str());
    //process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;

    QString dirverLetter = this->picSavePath.mid(0,1);
    QString writeText1 = dirverLetter + "\n";
    qDebug()<< writeText1<<endl;
    process.write(writeText1.toStdString().c_str());
    //process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;

    QString writeText2 = "git add " + picPath + "\n";
    process.write(writeText2.toStdString().c_str());
    //process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;

    process.write("git commit\n");
    //process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;

    process.write("git push\n");
    process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;


     ******************************暂时不使用上传*************************/

    //拼接远程图片路径
    gitPicPath.replace(QString("\\"), QString("/"));
    QString remotePicPath = "https://github.com/supermanc88/" + this->projectName + "/raw/master" + gitPicPath;

    QString clipText = remotePicPath;
    clipBoard->setText(clipText);

    //上传成功之后提示
    this->ui->label->setText(picPath);
    //上传完毕之后清空文件名
    this->ui->picSaveName->setText("");
}

void MainWindow::on_openPtn_clicked()
{
    QString ptnText = this->ui->openPtn->text();
    if(ptnText == "cancle")
    {
        this->ui->openPtn->setEnabled(true);
        this->ui->openPtn->setText("submit");
        this->ui->getClipboardBitmap->setEnabled(false);
    }
    else
    {
        this->picSavePath = this->ui->picSavePathLineEdit->text();
        if(this->ui->picSavePathLineEdit->text().at(this->ui->picSavePathLineEdit->text().length() - 1) != '\\')
        {
            this->picSavePath += "\\";
        }
        //根据文件保存路径向上遍历，找到git根路径，主要是为了拼接github路径
        QString tempPath = this->picSavePath;
        QString gitTextPath = tempPath + "\\.git";
        QDir * dirPath = new QDir(gitTextPath);

        while(!dirPath->exists())
        {
            QDir cdupPath(tempPath);
            cdupPath.cdUp();
            tempPath = cdupPath.path();
            gitTextPath = tempPath + "/.git";
            dirPath = new QDir(gitTextPath);
        }

        this->gitRootPath = tempPath;


        /***********************获取项目名***********************/
        if(tempPath.at(tempPath.length() -1 ) != "/")
        {
            tempPath += "/";
        }
        QStringList strList = tempPath.split('/');
        this->projectName = strList[ strList.size()-2 ];

        qDebug()<< "222222222"<<this->projectName<<endl;
        /***********************获取项目名***********************/


        this->ui->gitRootPaht->setText(this->gitRootPath);

        this->ui->picSavePathLineEdit->setEnabled(false);

        this->ui->openPtn->setText("cancle");
        this->ui->getClipboardBitmap->setEnabled(true);

    }

}

void MainWindow::uploadComplete()
{
    QMessageBox::warning(this,tr("upload"),tr("upload is ok"),QMessageBox::Yes);
}
