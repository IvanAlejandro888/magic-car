#include "all.h"


int crearSocket(int puerto){
    struct sockaddr_in direccionServidor;
    memset(&direccionServidor, 0, sizeof(direccionServidor));
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_addr.s_addr = htonl(INADDR_ANY);
    direccionServidor.sin_port = htons(puerto);

    int servidor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    int activado = 1;
    setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

    if(bind(servidor, (sockaddr *)&direccionServidor, sizeof(direccionServidor)) != 0){
        perror("bind");

        QMessageBox ebox;
        ebox.setWindowTitle("Error");
        ebox.setText("Cannot bind");
        ebox.setIcon(QMessageBox::Critical);
        ebox.exec();

        return -1;
    }

    printf("Estoy escuchando\n");
    listen(servidor, 100);

    /*-Aceptar conexiones y enviar informacion al cliente-----------------------------------*/
    /*--------------------------------------------------------------------------------------*/

    struct sockaddr_in direccionCliente;
    unsigned int tamanioDireccion;
    int cliente = accept(servidor, (sockaddr *)&direccionCliente, &tamanioDireccion);

    if(cliente >= 0){
        QMessageBox ebox;
        ebox.setWindowTitle("All ok!");
        ebox.setText("All done guy! Start playing!");
        ebox.setIcon(QMessageBox::Information);
        ebox.exec();
    }

    QMessageBox obox;
    QString msg;
    obox.setWindowTitle("Clients received!");
    msg = "Conexion stablished!";
    obox.setText(msg);
    obox.setIcon(QMessageBox::Information);
    obox.exec();

    return cliente;
}
