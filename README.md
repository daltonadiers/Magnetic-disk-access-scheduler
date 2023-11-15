# Escalonador de acessos a disco magnético
  Projeto desenvolvido para a cadeira de Sistemas Operacionais II, do curso de Ciência da Computação da Universidade de Passo Fundo.
  Este projeto visa simular os principais algoritmos utilizados no processo de escalonamento a disco, sendo eles FCFS(First-Come, First-Served), SSTF (Shortest Seek Time First), SCAN (Elevator), CIRCULAR SCAN, e C-LOOK.
## Descrição 
O algoritmo utiliza de duas classes principais, sendo a classe `scheduler` responsável por executar todos os diferentes algoritmos, enquanto a classe `printer` se responsabiliza por armazenar toda a informação e imprimir usando apenas uma systemCall, evitando paradas de sistema desnecessárias.
Para simular, consideramos um disco com 100 trilhas numeradas de 0 à 99. Cada vez que o algoritmo é executado, será gerada uma lista com 10 valores aleatórios entre 1 e 99 através da biblioteca `random`, simulando as requisições de acesso, além de um valor, também de 1 a 99 representando a posição inicial em que o cabeçote de leitura se encontra.
#### FCFS
Atenderá as requisições na mesma ordem em que chegaram, sem atribuir maiores lógicas de escolha.
#### SSTF
Atenderá as requisições de acordo com aquela que gerará menor deslocamento do cabeçote a partir da posição atual em que se encontra.
#### SCAN (Elevador)
Começará a atender as requisições em direção à trilha número 0. Se atingir o a trilha 0 e ainda houverem solicitações, deve seguir em direção crescente à trilha 99 até que não hajam mais requisições.
#### C-SCAN (Circular Scan)
Começará a atender as requisições em direção à trilha número 99, a partir de sua posição inicial. Se atingir a trilha 99 e ainda houverem solicitações, se deslocará imediatamente à trilha de número 0, e seguirá em direção crescente, até que não hajam mais requisições.
#### C-LOOK
Começará a atender as requisições em direção à trilha 99, a partir de sua posição inicial. Caso não hajam mais requisições entre sua posiçã atual e o 99, ele imediatamente irá se mover para a trilha de menor valor ainda não atendida, sem acessar as trilhas 99 e 0, prosseguindo em direção crescente até atender todas as requisições.
## Compilação e execução
#### Recomenda-se ambiente linux para execução do projeto
  1. Clone o repositório em um diretório de sua preferência
  2. Navegue via terminal até o diretório escolhido
  3. Compile o arquivo `initializer.cpp` utilizando no terminal a linha `g++ initializer.cpp -o nomedoarquivo` (substitua "nomedoarquivo" por um nome de sua preferência.)
  4. Execute utilizando no terminal a linha `./nomedoarquivo` (substitua "nomedoarquivo" pelo nome escolhido no passo anterior.)
## Linguagem de programação e compilador 
- **Linguagem:** C++
- **Compilador:** G++17 (Padrão C++17)
## Autores
- **Dalton Oberdan Adiers**@daltonadiers
- **Bruna Baldissera**@brunabaldissera
