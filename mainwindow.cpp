#include "mainwindow.h"
#include "./ui_mainwindow.h"

// fit one range to another
inline void normalize(std::vector<double>& data, const size_t& newMax)
{
    const auto [min, max] = std::minmax_element(data.begin(), data.end());

    const double oldRange {*max - *min};
    const double k = newMax / oldRange;

    std::transform(data.begin(), data.end(), data.begin(),
                   [&min, &k](double &n) {return ((n - *min) * k);});
}

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
    // exit
    this->close();
}

void MainWindow::on_btn_addFile_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("All files (*.s1p)"));
    // check if file choosed
    if (!fileName.isEmpty())
        readAndPlot(fileName);

    // throw a messagebox
    else
    {
        QMessageBox::warning(this, "Загрузка файла", "Файл не выбран");
        return;
    }
}

void MainWindow::readAndPlot(QString& fileName)
{
    Parser parser{};
    parser.read_file(fileName.toStdString());

    parser.freqs.emplace_back(0.);
    parser.data.emplace_back(0.);

    normalize(parser.freqs, (ui->graphicsView->width() * 0.9));
    normalize(parser.data, (ui->graphicsView->height() * 0.45));

    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    QPen pen(Qt::black);

    const size_t length = parser.freqs.size() - 1;

    for (size_t i = 1; i < length; ++i)
    {
        scene->addLine(
            parser.freqs[i - 1],
            -parser.data[i - 1],
            parser.freqs[i],
            -parser.data[i],
            pen
            );
    }

    pen.setColor(Qt::red);
    scene->addLine(
        parser.freqs[length + 1],
        -ui->graphicsView->height() * 0.45,
        parser.freqs[length + 1],
        ui->graphicsView->height() * 0.45,
        pen
        );

    scene->addLine(
        0,
        parser.data[length + 1],
        ui->graphicsView->width() * 0.9,
        parser.data[length + 1],
        pen
        );

    ui->graphicsView->setScene(scene);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    if (!fileName.isEmpty()) readAndPlot(fileName);
}

