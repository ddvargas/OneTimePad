# One-Time Pad

Programa implementado para a obtenção do grau de Bacharel em Sistemas de Informação,
na aula de Criptografia para Segurança de Dados da Universidade Federal de Santa Maria - UFSM.
O intuito é fornecer uma mensagem e o programa ser capaz de encriptá-la usando o
[algoritmo One Time Pad](https://pt.wikipedia.org/wiki/One-time_pad), gerarando uma cifra e uma chave. 
Também deve ser possível fazer o caminho inverso, decriptando, fornecendo uma chave e uma cifra.

#

### Modo de uso
Ao ser executado o programa solicitará se o usuário quer fazer uma operação de encriptação ou decriptação. 
   * Para a encriptação, o usuário especifica um arquivo .txt com o texto a ser encriptado. A saída será um arquivo nomeado "key.txt" com a chave gerada para aquela mensagem e um arquivo nomeado "cipher.txt" com a cifra para a mensagem. Ambos serão salvos no diretório em que o programa estiver sendo executado.
   * Para a decriptação, será solicitado o nome do arquivo de chave e cifra e também o nome do arquivo para a mensagem decriptada. Todos serão salvos no diretório em que o programa estiver sendo executado.
   
#  
   
### Compilando
Programa desenvlvido em C. Compile usando o CMake para compilar o projeto ou o GCC compilando o arquivo main.c.

Usando o CMake, o executável será  gerado com nome otpc. Usando o GCC, compile especificando um nome para o executável ou a saída será a padrão "a.out".

 
