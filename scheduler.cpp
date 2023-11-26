#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <stdlib.h>
#include <iomanip>
#include <string>

namespace edm{
    class printer{
        // Classe responsável por guardar e imprimir as informações geradas pelo scheduler
        public:
            // Concatena novas informações à string final
            void sumBuffer(std::string x){
                ansPrint+=x;
            }
            // Printa a string final "ansPrint", contendo as informações de todos os escalonamentos
            void print(){
                std::cout << ansPrint << "\n";
            }
        private:
            std::string ansPrint="";
    };
    class scheduler{
        // Classe responsável por executar os algoritmos de escalonamento
        public:
            void initializer(){
                geraRandom(); // Gera 10 requisições aleatórias com valores entre 1 e 99, e uma posição inicial também aleatória
                // Cada um dos 5 algoritmos serão executados
                fcfs();
                sstf();
                scan();
                cscan();
                clook();
                // Imprime tudo
                myPrinter.print();
            }
        private:
            printer myPrinter; // Instância da classe printer
            int requisicoes[10]; // Lista de requisições
            std::set<int> posicoes; // Como não fazemos alterações no array requisicoes, o set posicoes armazena temporariamente as posicoes que já foram atendidas por cada algoritmo
            int lastAcess =0, deslocamentos=0, posInicial, valueForDirection=0, backupforInitial;

            void geraRandom(){
                for(int i=0; i<11; i++){
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> distribution(1, 99);
                    if(i<10) requisicoes[i] = distribution(gen);
                    else posInicial = distribution(gen);
                }
                backupforInitial=posInicial;
            }
            // Utilizado para enviar para o buffer da classe printer o array original (antes da execução de quaisquer um dos algoritmos de escalonamento), e informar a posição inicial do cabeçote de leitura
            void printOriginal(){
                std::ostringstream output;
                output << "\n" << "Posição inicial da cabeça de leitura e gravação " << std::setw(2) << std::setfill('0') << posInicial << "\n";
                output << "Original [" << std::setw(2) << std::setfill('0') << requisicoes[0] << " - ";
                for(int i=1; i<10; i++){
                    output << std::setw(2) << std::setfill('0') << requisicoes[i];
                    if(i!=9)output << " - ";
                }
                output << "]\n\n";
                myPrinter.sumBuffer(output.str());
            }
            // Utilizado durante a execução dos algoritmos, para mostrar quais posições acessou e quais ainda pode acessar. Envia essas informações ao buffer da classe printer.
            void print(){
                std::ostringstream output;
                int meuTamanho = 10-(int)posicoes.size();
                int counter =0;
                output << "Acessou " << std::setw(2) << std::setfill('0') << lastAcess << "[";
                for(int i=0; i<10;i++){
                    if(posicoes.count(i)==0){
                        counter++;
                        output << std::setw(2) << std::setfill('0') << requisicoes[i];
                        if(counter==meuTamanho){
                            continue;
                        }else{
                            output << " - ";
                        }
                    }
                }
                output << "] Já deslocou " << deslocamentos << "\n";
                myPrinter.sumBuffer(output.str());
            }
            // Usado para zerar as variáveis globais, cada vez que formos executar um próximo algoritmo
            void zeroAll(){
                posInicial=backupforInitial,lastAcess=posInicial,deslocamentos=0;posicoes.clear();valueForDirection=posInicial;
            }
            // Utilizado apenas pelo C-Look, para saber o número da trilha que deve ir, ao atingir a requisição de maior número e ainda houverem mais requisições
            int foundMinValue(){
                int minValue =100;
                for(int i=0; i<10; i++){
                    if(requisicoes[i]<minValue && posicoes.count(i)==0)minValue=requisicoes[i];
                }
                return minValue;
            }
            // Função reaproveitada por Scan, C-Scan e C-Look, para ir em direção à borda do disco (trilha 99)
            void goUp(){
                    for(int i=0; i<10; i++){
                        bool mudei = false;
                        int minAbsFound =200, indexOfAbs=0;
                        for(int j=0; j<10; j++){
                            if(posicoes.count(j)==0 && requisicoes[j]>=valueForDirection){
                                if(abs(posInicial-requisicoes[j])<minAbsFound){
                                    minAbsFound=abs(posInicial-requisicoes[j]);
                                    indexOfAbs=j; mudei=true;
                                }
                            }
                        }
                        if(mudei){
                            lastAcess = requisicoes[indexOfAbs]; posicoes.insert(indexOfAbs);deslocamentos+=minAbsFound;posInicial=requisicoes[indexOfAbs];
                            print();
                        }
                    }
            }
            // Função utilizada para ir em direção ao centro do disco (trilha 0)
            void goDown(){
                    for(int i=0; i<10; i++){
                        int minAbsFound =200, indexOfAbs=0;
                        bool mudei = false;
                        for(int j=0; j<10; j++){
                            if(posicoes.count(j)==0 && requisicoes[j]<=valueForDirection){
                                if(abs(posInicial-requisicoes[j])<minAbsFound){
                                    minAbsFound=abs(posInicial-requisicoes[j]);
                                    indexOfAbs=j; mudei=true;
                                }
                            }
                        }
                        if(mudei){
                            lastAcess = requisicoes[indexOfAbs]; posicoes.insert(indexOfAbs);deslocamentos+=minAbsFound;posInicial=requisicoes[indexOfAbs];
                            print();
                        }
                    }
            }

            void fcfs(){
                printOriginal();
                std::ostringstream output;
                myPrinter.sumBuffer("========== Algoritmo FCFS! ==========\n");
                for(int i=0; i<10; i++){
                    lastAcess=requisicoes[i];
                    posicoes.insert(i);
                    deslocamentos += abs(posInicial-lastAcess);
                    posInicial=lastAcess;
                    print();
                }
                output << "FCFS - Quantidade total de deslocamentos: " << deslocamentos << "\n";
                myPrinter.sumBuffer(output.str());
            }
            void sstf(){
                std::ostringstream output;
                zeroAll();
                printOriginal();
                myPrinter.sumBuffer("========== Algoritmo SSTF! ==========\n");
                for(int i=0; i<10;i++){
                    int minAbsFound =200, indexOfAbs=0;
                    for(int j=0; j<10; j++){
                        if(posicoes.count(j)==0){
                            if(abs(posInicial-requisicoes[j])<minAbsFound){
                                minAbsFound=abs(posInicial-requisicoes[j]);
                                indexOfAbs=j;
                            }
                        }
                    }
                    lastAcess = requisicoes[indexOfAbs]; posicoes.insert(indexOfAbs);deslocamentos+=minAbsFound;posInicial=requisicoes[indexOfAbs];
                    print();
                }
                output << "SSTF - Quantidade total de deslocamentos: " << deslocamentos << "\n";
                myPrinter.sumBuffer(output.str());
            }

            void scan(){
                std::ostringstream output;
                zeroAll();
                printOriginal();
                myPrinter.sumBuffer("===== Algoritmo Scan (elevador) =====\n");
                goDown();
                if(posicoes.size()!=10){
                    if(lastAcess!=0){
                        deslocamentos+=abs(lastAcess-0);lastAcess=0;posInicial=0;
                        print();
                    }
                    valueForDirection=0;
                    goUp();
                }
                output << "SCAN - Quantidade total de deslocamentos: " << deslocamentos << "\n";
                myPrinter.sumBuffer(output.str());
            }

            void cscan(){
                std::ostringstream output;
                zeroAll();
                printOriginal();
                myPrinter.sumBuffer("====== Algoritmo Circular SCAN ======\n");
                goUp();
                if(posicoes.size()!=10){
                    if(lastAcess!=99){
                        deslocamentos+=abs(lastAcess-99);lastAcess=99;posInicial=99;
                        print();
                    }
                    deslocamentos+=abs(lastAcess-0);lastAcess=0;posInicial=0;
                    print();
                    valueForDirection=0;
                    goUp();
                }
                output << "Circular Scan - Quantidade total de deslocamentos: " << deslocamentos << "\n";
                myPrinter.sumBuffer(output.str());
            }
            void clook(){
                std::ostringstream output;
                zeroAll();
                printOriginal();
                myPrinter.sumBuffer("========= Algoritmo C-look ==========\n");
                goUp();
                if(posicoes.size()!=10){
                    int b = foundMinValue();
                    deslocamentos+=abs(lastAcess-b);lastAcess=0;posInicial=b;//posicoes.insert(b);
                    valueForDirection=0;
                    goUp();
                }
                output << "C-look - Quantidade total de deslocamentos: " << deslocamentos << "\n";
                myPrinter.sumBuffer(output.str());
            }
    };
}
