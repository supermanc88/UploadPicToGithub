#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
