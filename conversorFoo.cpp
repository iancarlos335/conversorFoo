/*
    2212006 - Ian Carlos Azevedo Martins
    2231823 - Nicole Santarosa de Luca
    2223579 - Rafael Calixto Avelar Marcelino
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void pegarNumeroDeLinhasEColunas(ifstream &arquivoDeLeitura, int matrizInfo[2])
{
    char caractere;
    string linha;

    while (arquivoDeLeitura.read(&caractere, sizeof(char)))
    {
        if (caractere != ' ')
            linha += caractere;
        else
        {
            matrizInfo[0] = std::stoi(linha);
            linha = "";
        }

        if (caractere == '\n')
        {
            matrizInfo[1] = std::stoi(linha);
            break;
        }
    }

    cout << "Numero de linhas: " << matrizInfo[0] << endl;
    cout << "Numero de colunas: " << matrizInfo[1] << endl;
}

void lerConteudoDoArquivoOrigem(char *nomeArquivo, int **matrizPixels)
{
    unsigned char caractere;
    int numeroLinha = 0;
    int matrizInfo[2] = {0, 0}; // primeira dimensão é o número de linhas, a segunda é o número de colunas

    ifstream arquivoDeLeitura(nomeArquivo, ios::binary);

    if (!arquivoDeLeitura)
    {
        std::cerr << "Erro abrindo o arquivo: " << nomeArquivo << std::endl;
        exit(-1);
    }

    pegarNumeroDeLinhasEColunas(arquivoDeLeitura, matrizInfo);

    matrizPixels = new int *[matrizInfo[0]];

    while (!arquivoDeLeitura.eof())
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

    for (int i = 0; i < matrizInfo[0]; i++)
    {
        delete &matrizPixels[i];
    }

    delete matrizPixels[matrizInfo[0]];

    arquivoDeLeitura.close();
}

void escreverNoArquivoFinal(char *nomeArquivo, int **matrizPixels)
{
    ofstream arquivoDeEscrita(nomeArquivo, ios::binary);

    arquivoDeEscrita.close();
}

int main(int argc, char *argv[])
{
    int **matrizPixels;

    char nomeArquivo[19] = "exemplos/img0.foo";

    cout << nomeArquivo << endl;
    lerConteudoDoArquivoOrigem(nomeArquivo, matrizPixels);

    escreverNoArquivoFinal(argv[2], matrizPixels);

    return 0;
}