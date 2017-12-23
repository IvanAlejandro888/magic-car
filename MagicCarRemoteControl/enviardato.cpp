#include "all.h"

void enviarDato(int cliente, char * mensaje){
    int envio = write(cliente, mensaje, strlen(mensaje));
    if(envio < 0){
        perror("write");
        QMessageBox ebox;
        ebox.setWindowTitle("Error");
        ebox.setText("Write data");
        ebox.setIcon(QMessageBox::Critical);
        ebox.exec();
    }

}
