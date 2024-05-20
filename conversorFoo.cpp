/*
    2212006 - Ian Carlos Azevedo Martins
    2231823 - Nicole Santarosa de Luca
    2223579 - Rafael Calixto Avelar Marcelino
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void pegarMaximoNumeroDeLinhasEColunas(ifstream arquivoDeLeitura, int *matrizInfo)
{
    char caractere;
    string linha;
    int matrizInfo[2]; // primeira dimensão é o número de linhas, segunda é o número de colunas
    int maiorNumeroColunas = 0;

    while (arquivoDeLeitura >> caractere)
    {
        matrizInfo[1]++;

        if (caractere == '\n')
        {
            maiorNumeroColunas = matrizInfo[1] > maiorNumeroColunas ? matrizInfo[1] : maiorNumeroColunas;
            matrizInfo[1] = 0;
            matrizInfo[0]++;
        }
    }

    arquivoDeLeitura.close();
}

void lerConteudoDoArquivoOrigem(string nomeArquivo, int **matrizPixels)
{
    unsigned char caractere;
    int numeroLinha = 0;
    int matrizInfo[2];

    ifstream arquivoDeLeitura(nomeArquivo, ios::binary);

    matrizPixels = new int *[matrizInfo[0]];

    while (arquivoDeLeitura >> caractere)
    {
        if (numeroLinha == 0)
        {
            numeroLinha++;
            continue;
        }
        else
        {
            numeroLinha++;
            matrizPixels[numeroLinha] = new int[matrizInfo[1]];
            cout << (int)caractere << ' ';
        }
    }

    int **matrizPixels = new int *[matrizInfo[0]];

    for (int i = 0; i < matrizInfo[0]; i++)
    {
        delete &matrizPixels[i];
    }

    delete matrizPixels[matrizInfo[0]];
    arquivoDeLeitura.close();
}

int main()
{
    string nomeArquivo = "exemplos/img0.foo";
    int **matrizPixels;

    lerConteudoDoArquivoOrigem(nomeArquivo, matrizPixels);

    return 0;
}