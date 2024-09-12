#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btn_exit_clicked()
{
    // выход из приложения
    // this->close();
    ui->label->setText(QString::number(ui->graphicsView->size().height()));
}


void MainWindow::on_btn_addFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.s1p)"));
    // проверка, выбран ли файл
    if (!fileName.isEmpty()) {
        QMessageBox::about(this, "debug:", "Yes");
    }
    // выход, если файл не найден
    else {
        QMessageBox::warning(this, "Загрузка файла", "Файл не выбран");
        return;
    }


    // одобавление осей
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    QPen pen(Qt::red);
    scene->addLine(0,90,180,90,pen);//x
    scene->addLine(90,0,90,180,pen);//y

    // отрисовка графика
    ui->graphicsView->setScene(scene);

}

