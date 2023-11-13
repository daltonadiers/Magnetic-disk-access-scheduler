#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <stdlib.h>

using namespace std;

int requisicoes[10];
set<int> posicoes;
int lastAcess =0, deslocamentos=0, posInicial, valueForDirection=0, backupforInitial;
bool whatDirection = false;   // FALSE DIRECIONA PARA BAIXO, TRUE PARA CIMA
bool directionForC = false;    // FALSE DIRECIONA PARA BAIXO, TRUE PARA CIMA


void fillRebonatto(){
    requisicoes[0]=30;
    requisicoes[1]=70;
    requisicoes[2]=54;
    requisicoes[3]=59;
    requisicoes[4]=29;
    requisicoes[5]=64;
    requisicoes[6]=87;
    requisicoes[7]=38;
    requisicoes[8]=05;
    requisicoes[9]=40;
    posInicial=88;
    backupforInitial=posInicial;
}

void geraRandom(){
    for(int i=0; i<11; i++){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(1, 100);
        if(i<10) requisicoes[i] = distribution(gen);
        else posInicial = distribution(gen);
    }
    backupforInitial=posInicial;
}
void changeDirection(){
    if(posInicial<=50)whatDirection= true;
    if(posInicial>=50)directionForC = true;
    valueForDirection=posInicial;
}
void printOriginal(){
    cout << "\n" << "Posição inicial da cabeça de leitura e gravação " << posInicial << "\n";
    cout << "Original [" << requisicoes[0] << " - ";
    for(int i=1; i<10; i++){
        cout << requisicoes[i];
        if(i!=9)cout << " - ";
    }
    cout << "]\n\n";
}
void print(){
    int meuTamanho = 10-(int)posicoes.size();
    int counter =0;
    cout << "Acessou " << lastAcess << "[";
    for(int i=0; i<10;i++){
        if(posicoes.count(i)==0){
            counter++;
            cout << requisicoes[i];
            if(counter==meuTamanho){
                continue;
            }else{
                cout << " - ";
            }
        }
    }
    cout << "] Já deslocou " << deslocamentos << "\n";
}

void zeroAll(){
    posInicial=backupforInitial,lastAcess=posInicial,deslocamentos=0;posicoes.clear();
}
void fcfs(){
    cout << "========== Algoritmo FCFS! ==========" << "\n";
    for(int i=0; i<10; i++){
        lastAcess=requisicoes[i];
        posicoes.insert(i);
        deslocamentos += abs(posInicial-lastAcess);
        posInicial=lastAcess;
        print();
    }
    cout << "FCFS - Quantidade total de deslocamentos: " << deslocamentos << "\n";
    printOriginal();
}
void sstf(){
    zeroAll();
    cout << "========== Algoritmo SSTF! ==========\n";
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
    cout << "SSTF - Quantidade total de deslocamentos: " << deslocamentos << "\n";
    printOriginal();
}

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

void scan(){
    zeroAll();
    changeDirection();
    cout << "===== Algoritmo Scan (elevador) =====\n";
    if(whatDirection){   //INDO PARA CIMA
        //cout << "go up primeiro\n";
        goUp();
        size_t setSize = posicoes.size();
        if(setSize<10){
            goDown();
        }
    }else{
        //cout << "go down primeiro\n";
        goDown();
        size_t setSize = posicoes.size();
        if(setSize<10){
            goUp();
        }
    }
    cout << "SCAN - Quantidade total de deslocamentos: " << deslocamentos << "\n";
    printOriginal();
}

void cscan(){
    zeroAll();
    changeDirection();
    cout << "====== Algoritmo Circular SCAN ======\n";
    if(directionForC){   //INDO PARA CIMA
        goUp();
        size_t setSize = posicoes.size();
        if(setSize<10){
            valueForDirection=0;
            if(lastAcess!=99){
                deslocamentos+=abs(lastAcess-99);lastAcess=99;
                print();
            }
            deslocamentos+=99;posInicial=0,lastAcess=0;
            print();
            goUp();
        }
    }else{
        goDown();
        size_t setSize = posicoes.size();
        if(setSize<10){
            valueForDirection=100;
            if(lastAcess!=0){
                deslocamentos+=abs(lastAcess-0);lastAcess=0;
                print();
            }
            deslocamentos+=99;posInicial=99,lastAcess=99;
            goDown();
        }
    }
    cout << "Circular Scan - Quantidade total de deslocamentos: " << deslocamentos << "\n";
    printOriginal();
}
void clook(){
    zeroAll();
    changeDirection();
    cout << "========= Algoritmo C-look ==========\n";
    if(directionForC){   //INDO PARA CIMA
        goUp();
        size_t setSize = posicoes.size();
        if(setSize<10){
            posInicial=100;
            for(int i=0; i<10; i++){
                if(requisicoes[i]<posInicial && posicoes.count(i)==0)posInicial=requisicoes[i];
            }
            deslocamentos+=abs(lastAcess-posInicial);
            valueForDirection=0;
            goUp();
        }
    }else{
        cout << "Go down primeiro?" << endl;
        goDown();
        size_t setSize = posicoes.size();
        if(setSize<10){
            posInicial=0;
            for(int i=0; i<10; i++){
                if(requisicoes[i]>posInicial && posicoes.count(i)==0)posInicial=requisicoes[i];
            }
            deslocamentos+=abs(lastAcess-posInicial);
            valueForDirection=100;
            goDown();
        }
    }
    cout << "C-look - Quantidade total de deslocamentos: " << deslocamentos << "\n";
    printOriginal();
}


void init(){
    //fillRebonatto();
    geraRandom();
    fcfs();
    sstf();
    scan();
    cscan();
    clook();
}

int main(){
    init();
    return 0;
}