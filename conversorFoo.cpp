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
            matrizInfo[1] = std::stoi(linha);
            linha = "";
        }

        if (caractere == '\n')
        {
            matrizInfo[0] = std::stoi(linha);
            break;
        }
    }

    cout << "Numero de linhas: " << matrizInfo[0] << endl;
    cout << "Numero de colunas: " << matrizInfo[1] << endl;
}

void lerConteudoDoArquivoOrigem(char *nomeArquivo, unsigned char **matrizPixels)
{
    unsigned char pixels;
    int contadorLinha = 0;
    int contadorColuna = 0;
    int matrizInfo[2] = {0, 0}; // primeira dimensão é o número de linhas, a segunda é o número de colunas

    ifstream arquivoDeLeitura(nomeArquivo, ios::binary);

    if (!arquivoDeLeitura)
    {
        std::cerr << "Erro abrindo o arquivo: " << nomeArquivo << std::endl;
        exit(-1);
    }

    pegarNumeroDeLinhasEColunas(arquivoDeLeitura, matrizInfo);

    matrizPixels = new unsigned char *[matrizInfo[0]];
    matrizPixels[contadorLinha] = new unsigned char[matrizInfo[1]];

    while (!arquivoDeLeitura.eof())
    {
        while (arquivoDeLeitura.read((char *)&pixels, sizeof(unsigned char)))
        {
            if (contadorColuna == matrizInfo[1] - 1)
            {
                matrizPixels[++contadorLinha] = new unsigned char[matrizInfo[1]];
                contadorColuna = 0;
            }

            matrizPixels[contadorLinha][contadorColuna++] = pixels;
        }
    }

    for (int i = 0; i < matrizInfo[0]; i++)
    {
        for (int j = 0; j < matrizInfo[1]; j++)
        {
            cout << (unsigned int)matrizPixels[i][j] << " ";
        }
    }

    delete matrizPixels[matrizInfo[0]];

    arquivoDeLeitura.close();
}

void escreverNoArquivoFinal(char *nomeArquivo, unsigned char **matrizPixels)
{
    ofstream arquivoDeEscrita(nomeArquivo, ios::binary);

    arquivoDeEscrita.close();
}

int main(int argc, char *argv[])
{
    unsigned char **matrizPixels;

    char nomeArquivo[19] = "exemplos/img0.foo";

    cout << nomeArquivo << endl;
    lerConteudoDoArquivoOrigem(nomeArquivo, matrizPixels);

    escreverNoArquivoFinal(argv[2], matrizPixels);

    return 0;
}