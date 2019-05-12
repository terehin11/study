#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mapcontrol.h>
#include <osmmapadapter.h>
#include <maplayer.h>
#include <imagepoint.h>
#include <circlepoint.h>
#include <linestring.h>
#include "flightplan.h"
#include <vector>
#include "dialog.h"
#include <QJsonDocument>

namespace Ui {
class MainWindow;
}
using namespace qmapcontrol;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    FlightPlan* plan;
    Layer* layer;
    Dialog* dg;
    QList<Point*> points;
    std::vector <double> vec_x;
    std::vector <double> vec_y;

public slots:
        void coordinateClicked(const QMouseEvent*, const QPointF);
        void resizeEvent(QResizeEvent *qEvent);
        void action();
        void deletePoint();
        void destroyDialog();

private slots:
        void on_zoomInButton_clicked();
        void on_zoomOutButton_clicked();

        void on_downloadFileButton_clicked();

        void on_unloadFileButton_clicked();

        void on_clearButton_clicked();

        void on_ExportKML_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
