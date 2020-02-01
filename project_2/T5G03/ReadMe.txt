Neste 2º projeto procuramos cumprir todos os requisitos, inclusive a validação de 
todos os inputs (com excepção da acentuação), implementando ainda algumas 
funcionalidades adicionais que consideramos que viriam a enriquecer o trabalho e 
a facilitar a utilização do programa desenvolvido.


Resumo do funcionamento do programa e das funcionalidades adicionais implementadas:

Inicialmente é pedido o ficheiro de texto da agência, devendo este ser inserido sem 
a extensão (.txt), já que esta é inserida “automaticamente”. No caso de o ficheiro 
não ser encontrado o programa termina, após mostrar uma mensagem que informa 
acerca do erro ocorrido na sua leitura.
A partir da leitura dos dados dos ficheiros da agência, dos clientes e dos pacotes 
de viagem, a implementação de classes, vetores, entre outros, facilitou a 
organização dos dados e sua gestão.
É apresentado ao utilizador um menu principal a partir do qual se pode aceder 
a sub-menus que permitem utilizar as diversas funcionalidades do programa.
É de salientar que, em todos os menus, é possível regressar ao menu anterior 
digitando “0” ou utilizando o atalho “Ctrl+z”;

O atalho “Ctrl+z” foi uma das funcionalidades que implementamos com o objetivo de 
facilitar a utilização do programa.  Este atalho permite voltar atrás em qualquer 
parte do programa dando assim a possibilidade de cancelar a execução de uma opção 
que tenha sido selecionada, desde que inserindo o ctrl-z antes de escrever os 
dados pedidos. Por exemplo, se o utilizador escolheu inserir um cliente, pode 
"voltar atrás" antes de o inserir efetivamente, bastando pressionar “Ctrl+z” 
antes de inserir os dados pedidos, isto é, inserindo ao invés do dado pedido 
( nome, nif,...), a opção “Ctrl+z”. Esta funcionalidade só não foi implementada 
quando é pedido uma data ou o preço por pessoa e, como foi explicado, 
não pode ser usada “a meio” de um input, mas sim no início.

Outra funcionalidade adicional é o facto de ser permitido ao utilizador modificar 
e remover os clientes/packets através do seu nif/identificador ou ainda mostrando 
uma lista resumida dos diferentes clientes/packets.

Por fim, ao mostrar os dados relativamente aos packs, tendo em consideração que no 
ficheiro de clientes e de packets podem constar originalmente informações que não 
estão sincronizadas entre si (no ficheiro dos clientes,por exemplo, existirem 
packets que não existem no ficheiro dos packets; o valor total das compras do 
cliente não estar de acordo com o preço dos packets), optamos por permitir ao 
cliente escolher se deseja ver os dados relativos aos packets vendidos de acordo 
com packets.txt ou de acordo com clients.txt.

Ao terminar o programa selecionando a opção EXIT ao inserir “0” (ou CTRL+Z) no 
menu principal, os dados são atualizados nos ficheiros originais.
