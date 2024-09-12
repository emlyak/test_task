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
    ui->label->setText(QString::number(ui->graphicsView->size().width()));
}

inline void normalize(std::vector<double>& data, const size_t& newMax)
{
        const auto [min, max] = std::minmax_element(data.begin(), data.end());

        const double oldRange {*max - *min};
        const double k = newMax / oldRange;

        std::transform(data.begin(), data.end(), data.begin(),
                      [&min, &k](double &n) {return ((n - *min) * k);});
}


void MainWindow::on_btn_addFile_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.s1p)"));
    // проверка, выбран ли файл
    if (!fileName.isEmpty()) {

        readAndPlot(fileName);


    }
    // выход, если файл не найден
    else {
        QMessageBox::warning(this, "Загрузка файла", "Файл не выбран");
        return;
    }

}

void MainWindow::readAndPlot(QString& fileName)
{
    Parser parser{};
    parser.read_file(fileName.toStdString());

    normalize(parser.freqs, (ui->graphicsView->width() * 0.9));
    normalize(parser.data, (ui->graphicsView->height() * 0.5));

    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    QPen pen(Qt::black);

    const size_t length = parser.freqs.size();

    for (size_t i = 1; i < length; ++i)
    {
        scene->addLine(
            parser.freqs[i - 1],
            parser.data[i - 1],
            parser.freqs[i],
            parser.data[i],
            pen
            );
    }

    ui->graphicsView->setScene(scene);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    if (!fileName.isEmpty()) readAndPlot(fileName);
    ui->label->setText("resized");
}

