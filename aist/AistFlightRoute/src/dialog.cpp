#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent, FlightPlan *bp, uint indx) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->indx = indx;
    dbp = bp;

    ui->param1SpinBox->setValue(static_cast<int>(bp->mission.items[indx].params[0]));
    ui->param2SpinBox->setValue(static_cast<int>(bp->mission.items[indx].params[1]));
    ui->param3SpinBox->setValue(static_cast<int>(bp->mission.items[indx].params[2]));
    ui->param4SpinBox->setValue(static_cast<int>(bp->mission.items[indx].params[3]));
    ui->latitudeSpinBox->setValue(bp->mission.items[indx].getLatitude());
    ui->longitudeSpinBox->setValue(bp->mission.items[indx].getLongitude());
    ui->heightSpinBox->setValue(bp->mission.items[indx].getAltitude());
    ui->autocontinueCheckBox->setChecked(bp->mission.items[indx].autoContinue);
    ui->commandSpinBox->setValue(bp->mission.items[indx].command);
    ui->doJumpIdSpinBox->setValue(bp->mission.items[indx].doJumpId);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_changeButton_clicked()
{
    dbp->mission.items[indx].setLatitude(ui->latitudeSpinBox->value());
    dbp->mission.items[indx].setLongitude(ui->longitudeSpinBox->value());
    dbp->mission.items[indx].setAltitude(ui->heightSpinBox->value());

    dbp->mission.items[indx].params[0] = ui->param1SpinBox->value();
    dbp->mission.items[indx].params[1] = ui->param2SpinBox->value();
    dbp->mission.items[indx].params[2] = ui->param3SpinBox->value();
    dbp->mission.items[indx].params[3] = ui->param4SpinBox->value();

    dbp->mission.items[indx].autoContinue = ui->autocontinueCheckBox->isChecked();
    dbp->mission.items[indx].command = ui->commandSpinBox->value();
    dbp->mission.items[indx].doJumpId = ui->doJumpIdSpinBox->value();


    emit exit();
}

void Dialog::on_stopButton_clicked()
{
    emit cancel();
}


void Dialog::on_deleteButton_clicked()
{
    dbp->mission.items.erase(dbp->mission.items.begin()+indx);
    emit pdelete();
}
