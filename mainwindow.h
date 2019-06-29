#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCharts>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void getPixelRow();
    void startApplication();
    void stopApplication();

private:
    QPushButton *_startButton;
    QPushButton *_stopButton;
    QLabel *_pixelRow;
    QTextEdit *_valuesDisplay;
    QTimer *_timer;

    QChartView *_chartView;
    QLineSeries *_serie;
    QChart *_chart;
    QValueAxis *_xAxis;
    QValueAxis *_yAxis;
};

#endif // MAINWINDOW_H
