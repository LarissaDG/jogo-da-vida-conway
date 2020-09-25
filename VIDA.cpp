#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#define linhas 50
#define colunas 50

using namespace std;

/*
@details
Linguagem: C++
Objetivo: Implementação do "Jogo da Vida" do matemático John Horton Conway
Main target: Implementation of John Horton Conway's: Game of Life 
Entrada: 
Saída: 
@date Útima alteração: 24/07/2020
@author  Larissa D G
@version 1.0
*/

struct tabuleiro
{
	char matriz[linhas][colunas];
};

void menu(){
	cout << "--------------------------------------------" << endl;
	cout << " Bem vindo ao jogo da vida! " << endl;
	cout << endl;
	cout << "Escolha uma das opcoes abaixo e digite \n o numero correspondente " << endl;
	cout << endl;
	cout << "1) Ler de um arquivo as posições originais " << endl;
	cout << "2) Gerar aleatóriamente " << endl;
	cout << "0) Sair " << endl;
	cout << "--------------------------------------------" << endl;
}

void inicializa (tabuleiro &vida){
	for(int i=0; i < linhas; i++){
		for(int j=0; j < colunas; j++){
			vida.matriz[i][j] = ' ';
		}
	}

}

void imprime (tabuleiro &vida){
	for(int i=0; i < linhas; i++){
		for(int j=0; j < colunas; j++){
			cout <<"|"<<vida.matriz[i][j];
		}
		cout << "|" << endl;
	}
}


int checavizinhos(tabuleiro &vida,int i, int j){
	int count = 0;
	if(vida.matriz[i][j+1] == '*'){
		count ++;
	}
	if(vida.matriz[i][j-1] == '*'){
		count ++;
	}
	if(vida.matriz[i+1][j] == '*'){
		count ++;
	}
	if(vida.matriz[i-1][j] == '*'){
		count ++;
	}
	if(vida.matriz[i+1][j+1] == '*'){
		count ++;
	}
	if(vida.matriz[i+1][j-1] == '*'){
		count ++;
	}
	if(vida.matriz[i-1][j+1] == '*'){
		count ++;
	}
	if(vida.matriz[i-1][j-1] == '*'){
		count ++;
	}
	return count;
}

void morre (tabuleiro &vida,int i, int j){
	vida.matriz[i][j] = ' ';
}

void nasce (tabuleiro &vida,int i, int j){
	vida.matriz[i][j] = '*';
}

void geracao(tabuleiro &vida){
    tabuleiro antigo;
    for(int i=0; i < linhas; i++){
        for(int j=0; j < colunas; j++){
            antigo.matriz[i][j] = vida.matriz[i][j];
        }
    }
    
	int vizinhos;
	for(int i=0; i < linhas; i++){
		for(int j=0; j < colunas; j++){
			if(vida.matriz[i][j] == '*'){
				vizinhos = checavizinhos(antigo,i,j);
				if(vizinhos <= 1 || vizinhos > 3){
					morre(vida,i,j);
					//imprime(vida);
				}
			}
			if(vida.matriz[i][j] == ' '){
				vizinhos = checavizinhos(antigo,i,j);
				if(vizinhos == 3){
					nasce(vida,i,j);
				}
			}
		}
		cout << endl;
	}
}


tabuleiro leArquivo(string &nomeArquivo, tabuleiro &vida){
	ifstream arq;
	int x,y;
	arq.open(nomeArquivo);
	while(arq >> x >> y){
		nasce(vida,x,y);
		//imprime(vida);
	}
	//imprime(vida);
	arq.close();
	return vida;
}

void celulasAleatorias(tabuleiro &vida){
	//srand((unsigned)time(nullptr));	
	int x,y;
	int numeroCelulas = rand() % (linhas*colunas);

	for(int i = 0; i < numeroCelulas; i++){
		x = rand()%linhas;
		y = rand()%colunas;
		nasce(vida,x,y);
	}
}

int main(){
	
	tabuleiro vida;
	string nomeArquivo;
	int opcao = 0, gen = 0, count = 1;
	do{
		do{
			menu();
			cin >> opcao;
			if(opcao > 2 || opcao < 0){
				//system("clear");
				cout << "Opção inválida " << endl;
			}
		}while(opcao > 2 || opcao < 0);
		if(opcao == 0){
			break;
		}
		system("clear");
		switch(opcao){
			case 1:
				cout << "Digite o número de gerações " << endl;
				cin >> gen;
				system("clear");

				inicializa(vida);
				cout << "Digite o nome do arquivo com .txt" << endl;
				
                getchar();
				getline(cin,nomeArquivo);
				

				vida = leArquivo (nomeArquivo, vida);
				system("clear");

				cout << "Tabuleiro original "<< endl; 

				imprime(vida);
				getchar();

				while(count <= gen){
					geracao(vida);
					system("clear");
					cout << "Tabuleiro geração num: "<< count << endl; 
					imprime(vida);
					count ++;
					getchar();
				}
				count = 1;
			
				break;
			case 2:
				cout << "Digite o número de gerações " << endl;
				cin >> gen;
				system("clear");

				inicializa(vida);
				celulasAleatorias(vida);

				cout << "Tabuleiro original "<< endl; 

				imprime(vida);

				getchar();

				getchar();

				while(count <= gen){
					geracao(vida);
					system("clear");
					cout << "Tabuleiro geração num: "<< count << endl; 
					imprime(vida);
					count ++;
					getchar();
				}
				count = 1;
				break;
			default: 
				cout << "Erro opção não cadastrada " << endl;
				break;

		}
	}while(opcao != 0);

	return 0;
}
