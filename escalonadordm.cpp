#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <stdlib.h>
#include <iomanip>

using namespace std;

int requisicoes[10];
set<int> posicoes;
int lastAcess =0, deslocamentos=0, posInicial, valueForDirection=0, backupforInitial;

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
        uniform_int_distribution<int> distribution(1, 99);
        if(i<10) requisicoes[i] = distribution(gen);
        else posInicial = distribution(gen);
    }
    backupforInitial=posInicial;
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
    cout << "Acessou " << setw(2) << setfill('0') << lastAcess << "[";
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
    posInicial=backupforInitial,lastAcess=posInicial,deslocamentos=0;posicoes.clear();valueForDirection=posInicial;
}

int foundMinValue(){
    int minValue =100;
    for(int i=0; i<10; i++){
        if(requisicoes[i]<minValue && posicoes.count(i)==0)minValue=requisicoes[i];
    }
    return minValue;
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

void fcfs(){
    printOriginal();
    cout << "========== Algoritmo FCFS! ==========" << "\n";
    for(int i=0; i<10; i++){
        lastAcess=requisicoes[i];
        posicoes.insert(i);
        deslocamentos += abs(posInicial-lastAcess);
        posInicial=lastAcess;
        print();
    }
    cout << "FCFS - Quantidade total de deslocamentos: " << deslocamentos << "\n";
}
void sstf(){
    zeroAll();
    printOriginal();
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
}

void scan(){
    zeroAll();
    printOriginal();
    cout << "===== Algoritmo Scan (elevador) =====\n";
    goDown();
    if(posicoes.size()!=10){
        if(lastAcess!=0){
            deslocamentos+=abs(lastAcess-0);lastAcess=0;posInicial=0;
            print();
        }
        valueForDirection=0;
        goUp();
    }
    cout << "SCAN - Quantidade total de deslocamentos: " << deslocamentos << "\n";
}

void cscan(){
    zeroAll();
    printOriginal();
    cout << "====== Algoritmo Circular SCAN ======\n";
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
    cout << "Circular Scan - Quantidade total de deslocamentos: " << deslocamentos << "\n";
}
void clook(){
    zeroAll();
    printOriginal();
    cout << "========= Algoritmo C-look ==========\n";
    goUp();
    if(posicoes.size()!=10){
        int b = foundMinValue();
        deslocamentos+=abs(lastAcess-b);lastAcess=0;posInicial=b;posicoes.insert(b);
        valueForDirection=0;
        goUp();
    }
    cout << "C-look - Quantidade total de deslocamentos: " << deslocamentos << "\n";
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