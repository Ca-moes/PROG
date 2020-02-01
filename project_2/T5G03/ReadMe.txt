Neste 2� projeto procuramos cumprir todos os requisitos, inclusive a valida��o de 
todos os inputs (com excep��o da acentua��o), implementando ainda algumas 
funcionalidades adicionais que consideramos que viriam a enriquecer o trabalho e 
a facilitar a utiliza��o do programa desenvolvido.


Resumo do funcionamento do programa e das funcionalidades adicionais implementadas:

Inicialmente � pedido o ficheiro de texto da ag�ncia, devendo este ser inserido sem 
a extens�o (.txt), j� que esta � inserida �automaticamente�. No caso de o ficheiro 
n�o ser encontrado o programa termina, ap�s mostrar uma mensagem que informa 
acerca do erro ocorrido na sua leitura.
A partir da leitura dos dados dos ficheiros da ag�ncia, dos clientes e dos pacotes 
de viagem, a implementa��o de classes, vetores, entre outros, facilitou a 
organiza��o dos dados e sua gest�o.
� apresentado ao utilizador um menu principal a partir do qual se pode aceder 
a sub-menus que permitem utilizar as diversas funcionalidades do programa.
� de salientar que, em todos os menus, � poss�vel regressar ao menu anterior 
digitando �0� ou utilizando o atalho �Ctrl+z�;

O atalho �Ctrl+z� foi uma das funcionalidades que implementamos com o objetivo de 
facilitar a utiliza��o do programa.  Este atalho permite voltar atr�s em qualquer 
parte do programa dando assim a possibilidade de cancelar a execu��o de uma op��o 
que tenha sido selecionada, desde que inserindo o ctrl-z antes de escrever os 
dados pedidos. Por exemplo, se o utilizador escolheu inserir um cliente, pode 
"voltar atr�s" antes de o inserir efetivamente, bastando pressionar �Ctrl+z� 
antes de inserir os dados pedidos, isto �, inserindo ao inv�s do dado pedido 
( nome, nif,...), a op��o �Ctrl+z�. Esta funcionalidade s� n�o foi implementada 
quando � pedido uma data ou o pre�o por pessoa e, como foi explicado, 
n�o pode ser usada �a meio� de um input, mas sim no in�cio.

Outra funcionalidade adicional � o facto de ser permitido ao utilizador modificar 
e remover os clientes/packets atrav�s do seu nif/identificador ou ainda mostrando 
uma lista resumida dos diferentes clientes/packets.

Por fim, ao mostrar os dados relativamente aos packs, tendo em considera��o que no 
ficheiro de clientes e de packets podem constar originalmente informa��es que n�o 
est�o sincronizadas entre si (no ficheiro dos clientes,por exemplo, existirem 
packets que n�o existem no ficheiro dos packets; o valor total das compras do 
cliente n�o estar de acordo com o pre�o dos packets), optamos por permitir ao 
cliente escolher se deseja ver os dados relativos aos packets vendidos de acordo 
com packets.txt ou de acordo com clients.txt.

Ao terminar o programa selecionando a op��o EXIT ao inserir �0� (ou CTRL+Z) no 
menu principal, os dados s�o atualizados nos ficheiros originais.
