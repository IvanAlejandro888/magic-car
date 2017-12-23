#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include "all.h"

int crearSocket(int puerto);
int enviarDato(int puerto, char * mensaje);
int terminarConexion(int server);

namespace Ui {
class RemoteControl;
}

class RemoteControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemoteControl(QWidget *parent = 0);
    ~RemoteControl();

private slots:
    void on_btnSetup_clicked();

    void on_btnFront_pressed();

    void on_btnFront_released();

    void on_btnBack_pressed();

    void on_btnBack_released();

    void on_btnLeft_pressed();

    void on_btnLeft_released();

    void on_btnRight_pressed();

    void on_btnRight_released();

private:
    Ui::RemoteControl *ui;
};

#endif // REMOTECONTROL_H
