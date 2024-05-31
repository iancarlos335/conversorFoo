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
    char linhaCompleta[9];
    string buffer = "";

    arquivoDeLeitura.read((char *)&linhaCompleta, 9);
    for (int i = 0; i < 9; i++)
    {
        if (linhaCompleta[i] != ' ' && linhaCompleta[i] != '\n' && linhaCompleta[i] != '\r')
        {
            buffer += linhaCompleta[i];
        }

        if (linhaCompleta[i] == ' ')
        {
            matrizInfo[1] = std::stoi(buffer);
            buffer = "";
        }

        if (linhaCompleta[i] == '\n')
        {
            matrizInfo[0] = std::stoi(buffer);
            break;
        }
    }

    cout << "Numero de linhas: " << matrizInfo[0] << endl;
    cout << "Numero de colunas: " << matrizInfo[1] << endl;
}

void lerConteudoDoArquivoOrigem(char *nomeArquivo, char **matrizPixels)
{
    int matrizInfo[2] = {0, 0}; // primeira dimensão é o número de linhas, a segunda é o número de colunas

    ifstream arquivoDeLeitura(nomeArquivo, ios::binary);

    if (!arquivoDeLeitura)
    {
        std::cerr << "Erro abrindo o arquivo: " << nomeArquivo << std::endl;
        exit(-1);
    }

    pegarNumeroDeLinhasEColunas(arquivoDeLeitura, matrizInfo);

    matrizPixels = new char *[matrizInfo[0]];
    for (int i = 0; i < matrizInfo[0]; i++)
    {
        matrizPixels[i] = new char[matrizInfo[1]];
        arquivoDeLeitura.read((char *)matrizPixels[i], matrizInfo[1]);
    }

    for (int i = 0; i < matrizInfo[0]; i++)
    {
        for (int j = 0; j < matrizInfo[1]; j++)
        {
            cout << matrizPixels[i][j];
        }
    }

    delete matrizPixels[matrizInfo[0]];

    arquivoDeLeitura.close();
}

void escreverNoArquivoFinal(char *nomeArquivo, char **matrizPixels)
{
    ofstream arquivoDeEscrita(nomeArquivo, ios::binary);

    arquivoDeEscrita.close();
}

int main(int argc, char *argv[])
{
    char **matrizPixels;

    char nomeArquivo[19] = "exemplos/img0.foo";

    cout << nomeArquivo << endl;
    lerConteudoDoArquivoOrigem(nomeArquivo, matrizPixels);

    escreverNoArquivoFinal(argv[2], matrizPixels);

    return 0;
}