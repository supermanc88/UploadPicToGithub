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
    this->ui->label->setText("1111111111111111111");
    QClipboard * clipBoard = QApplication::clipboard();
    QPixmap pixmap = clipBoard->pixmap();
    QString picPath("F:\\MarkDownPic\\Image\\test\\getpic2.png");
    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();
    QString dateTimeFormat = "yyyyMMddHHmmss";
    dateTimeFormat = dateTime.toString("yyyyMMddHHmmss");
    picPath = this->picSavePath + dateTimeFormat + ".png";
    qDebug()<<picPath;
    pixmap.save(picPath);

    //清空剪切板
    clipBoard->clear();

    QString clipText = "heeemy.cheng@gmail.com";
    clipBoard->setText(clipText);

    /*********************************************
     * 完成上传功能，但是卡顿严重
     *********************************************/

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

    process.write("git add ./\n");
    //process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;

    process.write("git commit -m \"qt add one pic\"\n");
    //process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;

    process.write("git push\n");
    process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;


     ******************************暂时不使用上传*************************/
    //上传成功之后提示
    this->ui->label->setText(picPath);
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
            gitTextPath = tempPath + "\\.git";
            dirPath = new QDir(gitTextPath);
        }

        this->gitRootPath = tempPath;

        this->ui->gitRootPaht->setText(this->gitRootPath);

        this->ui->picSavePathLineEdit->setEnabled(false);

        this->ui->openPtn->setText("cancle");
        this->ui->getClipboardBitmap->setEnabled(true);

    }

}
