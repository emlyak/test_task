#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include "parser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_exit_clicked();

    void on_btn_addFile_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;

    void resizeEvent(QResizeEvent* event);

    void readAndPlot(QString& fileName);
};
#endif // MAINWINDOW_H
