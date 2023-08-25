## Passo 1:

***Abra o VSCode* ou seu compilador favorito e selecione a pasta descompactada***

## Passo 2:

***Em seguida, abra um terminal e navegue para a pasta, (pode renomeá-lo para servidor se quiser). Neste terminal, execute os seguintes comandos:***

  `g++ server.cpp -o servidor -lws2_32`
  
  `.\servidor.exe`

## Passo 3:

***Abra quantos terminais quiser e renomeie-os para cliente, (por ex.: cliente 1, cliente 2, cliente 3, cliente 4, etc...). Nestes terminais denominados de cliente, execute os seguintes comandos:***
  
  `g++ client.cpp -o cliente-lws2_32`
  
  `.\cliente.exe`
