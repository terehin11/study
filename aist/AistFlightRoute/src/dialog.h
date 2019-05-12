#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "flightplan.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent, FlightPlan* bp, uint indx);
    ~Dialog();

    uint indx;
    FlightPlan* dbp;

private slots:
    void on_changeButton_clicked();
    void on_stopButton_clicked();

    void on_deleteButton_clicked();

signals:
    void exit();
    void cancel();
    void pdelete();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
