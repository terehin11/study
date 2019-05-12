#include "mainwindow.h"
#include <QPainter>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "Item.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plan = new FlightPlan();
    // create layer
    layer = new MapLayer("Custom Layer", new OSMMapAdapter());

    ui->mapControl->addLayer(layer);

     //Sets the view to the interesting area
    ui->mapControl->setView(QPointF(44.00205, 56.32867));
    ui->mapControl->setZoom(11);

    connect(ui->mapControl, SIGNAL(mouseEventCoordinate(const QMouseEvent*, const QPointF)),
            this, SLOT(coordinateClicked(const QMouseEvent*, const QPointF)));

    ui->mapControl->enablePersistentCache();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete layer;
    delete plan;
}
void MainWindow::action()
{
    dg->close();
    disconnect(dg, SIGNAL(exit()), this, SLOT(action()));
    disconnect(dg, SIGNAL(cancel()), this, SLOT(destroyDialog()));
    connect(dg, SIGNAL(pdelete()), this, SLOT(deletePoint()));

    int i = dg->indx;
    QPointF qpf;
    qpf.setX((qreal)plan->mission.items[i].getLongitude());
    qpf.setY((qreal)plan->mission.items[i].getLatitude());
    points.at(i)->setCoordinate(qpf);

    QPen* linepen = new QPen(QColor(255, 0, 0, 255));
    linepen->setWidth(5);
    LineString* ls = new LineString(points, "line", linepen);
    layer->clearGeometries();
    layer->addGeometry(ls);
    delete dg;

    ui->mapControl->updateView();
}
void MainWindow::destroyDialog()
{
    dg->close();
    disconnect(dg, SIGNAL(exit()), this, SLOT(action()));
    disconnect(dg, SIGNAL(cancel()), this, SLOT(destroyDialog()));
    connect(dg, SIGNAL(pdelete()), this, SLOT(deletePoint()));

    delete dg;
}

void MainWindow::deletePoint()
{
    dg->close();
    disconnect(dg, SIGNAL(exit()), this, SLOT(action()));
    disconnect(dg, SIGNAL(cancel()), this, SLOT(destroyDialog()));
    connect(dg, SIGNAL(pdelete()), this, SLOT(deletePoint()));

    int i = dg->indx;
    points.erase(points.begin()+i);

    QPen* linepen = new QPen(QColor(255, 0, 0, 255));
    linepen->setWidth(5);
    LineString* ls = new LineString(points, "line", linepen);
    layer->clearGeometries();
    layer->addGeometry(ls);

    delete dg;
}
void MainWindow::coordinateClicked(const QMouseEvent* evnt, const QPointF coord)
{
    if(!ui->addPointsCheckBox->isChecked() && !ui->editPointsCheckBox->isChecked())
    {
        return;
    }
    if(ui->editPointsCheckBox->isChecked() && evnt->type() == QEvent::MouseButtonPress)
    {
        double radius = sqrt(pow(coord.x(),2) + pow(coord.y(),2));
        for(int i(0); i < points.size(); i++)
        {
            double p_radius = sqrt(pow(points.at(i)->coordinate().x(),2) + pow(points.at(i)->coordinate().y(),2));
            if(fabs(radius-p_radius) < 0.0001)
            {
                qDebug() << i;
                dg = new Dialog(nullptr, plan, i);
                connect(dg, SIGNAL(exit()), this, SLOT(action()));
                connect(dg, SIGNAL(cancel()), this, SLOT(destroyDialog()));
                connect(dg, SIGNAL(pdelete()), this, SLOT(deletePoint()));
                dg->show();
            }
        }
    }
    else
    {
        if(evnt->type() == QEvent::MouseButtonPress)
        {
            QPen* pointpen = new QPen(QColor(0,255,0));
            pointpen->setWidth(3);
            points.append(new CirclePoint( coord.x(), coord.y(), "Marker",  Point::Middle, pointpen));
            QPen* linepen = new QPen(QColor(255, 0, 0, 255));
            linepen->setWidth(5);
            LineString* ls = new LineString(points, "line", linepen);
            layer->clearGeometries();
            layer->addGeometry(ls);
            Item i;
            i.setLongitude(coord.x());
            i.setLatitude(coord.y());
            i.setAltitude(5);
            plan->mission.items.push_back(i);

        }
    }
    ui->mapControl->updateView();
}

void MainWindow::resizeEvent(QResizeEvent *qEvent)
{
    if(qEvent->oldSize().width() <= 0 || qEvent->oldSize().height() <= 0)
    {
        return;
    }
    ui->mapControl->resize(ui->mapControl->geometry().size() + qEvent->size() - qEvent->oldSize());
}

void MainWindow::on_zoomInButton_clicked()
{
    ui->mapControl->zoomIn();
}

void MainWindow::on_zoomOutButton_clicked()
{
    ui->mapControl->zoomOut();
}

void MainWindow::on_downloadFileButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(0, "Загрузить конфигурацию полёта", "", "*.plan");
    QString val;
    QFile file;

    file.setFileName(file_path);
    val=QDir::homePath();
    if(!QFile::exists(file_path)){
        qDebug() << "file does not exists";
        return;
    }

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject root = document.object();

    plan->loadFromJson(root);

    QPen* pointpen = new QPen(QColor(0,255,0));
    pointpen->setWidth(3);

    for(int i(0); i < plan->mission.items.size(); i++)
    {
        points.append(new CirclePoint(plan->mission.items[i].getLongitude(), plan->mission.items[i].getLatitude(), "Marker",  Point::Middle, pointpen));
    }
    QPen* linepen = new QPen(QColor(255, 0, 0, 255));
    linepen->setWidth(5);
    LineString* ls = new LineString(points, "line", linepen);
    layer->clearGeometries();
    layer->addGeometry(ls);

    ui->mapControl->updateView();

}

void MainWindow::on_unloadFileButton_clicked()
{

    QString file_path = QFileDialog::getSaveFileName(0, "Выгрузить конфигурацию полёта", "", "*.plan");

    QFile file(file_path);
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "can't open file";
        return;
    };

    plan->toJson();
    QJsonDocument doc(plan->toJson());
    QByteArray byteArray = doc.toJson();
    file.write(byteArray);
    file.close();
}

void MainWindow::on_clearButton_clicked()
{
    plan->mission.items.clear();
    points.clear();
    layer->clearGeometries();
    ui->mapControl->updateView();
}

void MainWindow::on_ExportKML_clicked()
{
    plan->ExportKML();
}
