#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>

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
    qDebug()<<picPath;
    pixmap.save(picPath);

    //清空剪切板
    clipBoard->clear();

    QString clipText = "heeemy.cheng@gmail.com";
    clipBoard->setText(clipText);

    /*********************************************
     * 完成上传功能，但是卡顿严重
     *********************************************/
    QProcess process;
    process.start("cmd");
    process.waitForStarted();
    process.write("cd F:\\MarkDownPic\\Image\\\n");
    //process.closeWriteChannel();
    process.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(process.readAllStandardOutput())<<endl;

    process.write("F:\n");
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
}
