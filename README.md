# Portscan

PortScan escrito na linguagem C

### Modo de usar
Compile o arquivo
gcc portscan.c -o portscan

Para varrer todas as portas disponiveis:
./portscan 192.168.0.1

Para varrer até determinada porta 
./portscan 192.168.0.1 49152

Para varrer em um intervalo de portas
./portscan 192.168.0.1 1024 49152
