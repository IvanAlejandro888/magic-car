#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void){
	/*-Crear un servidor, asociarlo a un puerto y ponerlo en escucha------------------------*/
	/*--------------------------------------------------------------------------------------*/

	struct sockaddr_in direccionServidor;
	memset(&direccionServidor, 0, sizeof(direccionServidor));
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = htonl(INADDR_ANY);
	direccionServidor.sin_port = htons(9000);

	int servidor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	if(bind(servidor, (void *)&direccionServidor, sizeof(direccionServidor)) != 0){
		perror("bind");
		return 1;
	}

	printf("Estoy escuchando\n");
	listen(servidor, 100);

	/*-Aceptar conexiones y enviar informacion al cliente-----------------------------------*/
	/*--------------------------------------------------------------------------------------*/

	struct sockaddr_in direccionCliente;
	unsigned int tamanioDireccion;
	int cliente = accept(servidor, (void *)&direccionCliente, &tamanioDireccion);

	printf("Recibi una conexion en %d!!\n", cliente);

	char c1[]  = "CODIGO 1\r";
	char c2[] = "CODIGO 0\r";

	while (1) {
		write(cliente, c1, strlen(c1));
		sleep(1);
		write(cliente, c2, strlen(c2));
		sleep(1);
	}
//
//	/*-Recibir mensajes---------------------------------------------------------------------*/
//	/*--------------------------------------------------------------------------------------*/
//
//	char* buffer = malloc(1000);
//
//	while(1){
//		int bytesRecibidos = recv(cliente, buffer, 1000, 0);
//		if(bytesRecibidos <= 0){
//			perror("recv");
//			return 1;
//		}
//
//		buffer[bytesRecibidos] = '\0';
//		printf("Me llegaron %d bytes con %s\n", bytesRecibidos, buffer);
//	}
//
//	free(buffer);

	return 0;
}
