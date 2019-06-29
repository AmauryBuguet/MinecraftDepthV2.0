#include "mainwindow.h"
#include "unistd.h"

#define WIDTH 10
#define HEIGHT 600

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(650,HEIGHT + 40);

    _startButton = new QPushButton("START", this);
    _startButton->setFixedSize(150,50);
    _startButton->setGeometry(180,40,150,50);

    _stopButton = new QPushButton("STOP", this);
    _stopButton->setFixedSize(150,50);
    _stopButton->setGeometry(180,120,150,50);

    _pixelRow = new QLabel(this);
    _pixelRow->setGeometry(500,20,WIDTH,HEIGHT);
    _pixelRow->setStyleSheet("border: 1px solid black");

    _valuesDisplay = new QTextEdit(this);
    _valuesDisplay->setGeometry(550, 20, 60, HEIGHT);
    _valuesDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _timer = new QTimer(this);
    _timer->setInterval(200);

    // CHART
    _serie = new QLineSeries();

    QPen pen(Qt::blue);
    _serie->setPen(pen);

    _chart = new QChart();
    _chart->legend()->hide();
    _chart->addSeries(_serie);
    _chart->layout()->setContentsMargins(0, 0, 0, 0);

    _xAxis = new QValueAxis();
    _xAxis->setTitleText("Height");
    _xAxis->setLabelFormat("%d");
    _xAxis->setRange(0, 600);

    _yAxis = new QValueAxis();
    _yAxis->setLabelFormat("%d");
    _yAxis->setTitleText("Distance ");
    _yAxis->setRange(150,255);

    _chart->addAxis(_xAxis, Qt::AlignBottom);
    _chart->addAxis(_yAxis, Qt::AlignLeft);

    _serie->attachAxis(_xAxis);
    _serie->attachAxis(_yAxis);

    _chart->setTitle("Depth line");

    _chartView = new QChartView(this);
    _chartView->setRenderHint(QPainter::Antialiasing);
    _chartView->setChart(_chart);
    _chartView->rotate(90);
    _chartView->setGeometry(20, 195, 450, 400);

    connect(_timer, &QTimer::timeout, this, &MainWindow::getPixelRow);
    connect(_startButton, &QPushButton::clicked, this, &MainWindow::startApplication);
    connect(_stopButton, &QPushButton::clicked, this, &MainWindow::stopApplication);
}

MainWindow::~MainWindow()
{

}

void MainWindow::startApplication()
{
    sleep(4);
    _timer->start();
}

void MainWindow::stopApplication()
{
    _timer->stop();
}

void MainWindow::getPixelRow()
{
    _valuesDisplay->clear();
    _serie->clear();
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pix = screen->grabWindow(0,1010,50,WIDTH,HEIGHT);
    QImage img = pix.toImage();
    _pixelRow->setPixmap(pix);
    int tempvalue;
    for (int i = 1; i < 36; ++i){
        tempvalue = QColor(img.pixel(8,i*17)).black();
        _valuesDisplay->append(QString::number(tempvalue));
        _serie->append(i*17, tempvalue);
    }
}
