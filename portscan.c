#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

#define INICIO 0
#define FINAL 65535

bool validacao(int argc, char *ip){
	if(argc < 2 || argc > 4){
		printf("Insira um IP para escanear as portas!\n");
		fflush(stdout);
		return true;
	}
	struct in_addr ip4;
	if(!inet_pton(AF_INET, ip, &ip4)){
		printf("Formato de IP Invalido!\n");
		fflush(stdout);
		return true;
	}
	return false;
}

int get_inicio(int argc, char *argv[]){
	int inicio = argc == 4 ? atoi(argv[2]) : INICIO;
	return inicio < INICIO ? INICIO : inicio;
}

int get_final(int argc, char *argv[]){
	int final = argc == 4 ? atoi(argv[3]) : argc == 3 ? atoi(argv[2]) : FINAL;
	return final > FINAL ? FINAL : final;
}

void loading(int atual, int final){
	printf("Scaneando porta %d de %d", atual, final);
	fflush(stdout);
	printf("\r                                          \r");
	return;
}

int main(int argc, char *argv[]){
	if(validacao(argc, argv[1])){
		return 1;
	}
	int meusocket;
	int conecta;
	int porta;
	int inicio = get_inicio(argc, argv);
	int final = get_final(argc, argv);
	char *destino;
	destino = argv[1];
	struct sockaddr_in alvo;
	
	printf("Escaneando alvo %s da porta %d a %d\n", destino, inicio, final);
	fflush(stdout);

	for (porta=inicio; porta <= final; porta++){
		meusocket = socket(AF_INET, SOCK_STREAM, 0);
		alvo.sin_family = AF_INET;
		alvo.sin_port = htons(porta);
		alvo.sin_addr.s_addr = inet_addr(destino);
		
		conecta = connect(meusocket, (struct sockaddr *)&alvo, sizeof alvo);
		if(conecta == 0){
			printf("Porta %d - status [ABERTA]\n", porta);
			fflush(stdout);
		}
		close(meusocket);
		loading(porta, final);
	}
	return 0;
}
