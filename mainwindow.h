#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

//只是声明类，在cpp文件中再引入头文件
class QString;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * 从当前剪贴板获取位图信息并保存
     * @brief GetPicFromCurrentClipBoard
     */
    void GetPicFromCurrentClipBoard();

private slots:
    void on_getClipboardBitmap_clicked();

    void on_openPtn_clicked();

private:
    Ui::MainWindow *ui;
    QString picSavePath;
    QString gitRootPath;
//    QProcess process;
};

#endif // MAINWINDOW_H
