#include "remotecontrol.h"
#include "ui_remotecontrol.h"

int ret;
QString puerto;

RemoteControl::RemoteControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemoteControl)
{
    ui->setupUi(this);
}

RemoteControl::~RemoteControl()
{
    delete ui;
}

void RemoteControl::on_btnSetup_clicked()
{
    bool ok;
    puerto = QInputDialog::getText(this, tr(""),
                                       tr("Port:"), QLineEdit::Normal,
                                       "", &ok);
    if (ok && !puerto.isEmpty()){
      ret = crearSocket(puerto.toInt());

      if(ret!=-1){
          ui->btnLeft->setEnabled(true);
          ui->btnRight->setEnabled(true);
          ui->btnFront->setEnabled(true);
          ui->btnBack->setEnabled(true);
      }
    }
}

// Avanzar

void RemoteControl::on_btnFront_pressed()
{
    enviarDato(ret, "FORWARD\r");
}


void RemoteControl::on_btnFront_released()
{
    enviarDato(ret, "STOP\r");
}

// Retroceder

void RemoteControl::on_btnBack_pressed()
{
    enviarDato(ret, "BACKWARD\r");
}

void RemoteControl::on_btnBack_released()
{
    enviarDato(ret, "STOP\r");
}

// Girar a la izquierda

void RemoteControl::on_btnLeft_pressed()
{
    enviarDato(ret, "TURN_LEFT\r");
}

void RemoteControl::on_btnLeft_released()
{
    enviarDato(ret, "STOP\r");
}

// Girar a la derecha

void RemoteControl::on_btnRight_pressed()
{
    enviarDato(ret, "TURN_RIGHT\r");
}

void RemoteControl::on_btnRight_released()
{
    enviarDato(ret, "STOP\r");
}
