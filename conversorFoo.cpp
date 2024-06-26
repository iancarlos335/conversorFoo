/*
    2212006 - Ian Carlos Azevedo Martins
    2231823 - Nicole Santarosa de Luca
    2223579 - Rafael Calixto Avelar Marcelino
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void pegarDimensoesDaImagem(ifstream &arquivoDeLeitura, int matrizInfo[2])
{
    char linhaCompleta[9];
    string buffer = ""; // buffer para capturar as informações da imagem e contruir a futura matriz de pixels

    arquivoDeLeitura.read((char *)&linhaCompleta, 9);
    for (int i = 0; i < 9; i++)
    {
        if (linhaCompleta[i] != ' ' && linhaCompleta[i] != '\n' && linhaCompleta[i] != '\r')
        {
            buffer += linhaCompleta[i];
        }

        if (linhaCompleta[i] == ' ')
        {
            matrizInfo[1] = stoi(buffer);
            buffer = "";
        }

        if (linhaCompleta[i] == '\n')
        {
            matrizInfo[0] = stoi(buffer);
            break;
        }
    }

    cout << "Numero de linhas: " << matrizInfo[0] << endl;
    cout << "Numero de colunas: " << matrizInfo[1] << endl;
}

void lerConteudoDoArquivoOrigem(ifstream &arquivoDeLeitura, int **&matrizPixels, int matrizInfo[2], char *dimensoesImagem)
{
    unsigned char **matrizCaracteres;

    // Le as dimensões da imagem e coloca num vetor de char
    arquivoDeLeitura.seekg(0);
    arquivoDeLeitura.read((char *)dimensoesImagem, 8);

    // Le o conteúdo da imagem e alimenta a matriz de pixels
    matrizCaracteres = new unsigned char *[matrizInfo[0]];
    for (int i = 0; i < matrizInfo[0]; i++)
    {
        matrizCaracteres[i] = new unsigned char[matrizInfo[1]];
        arquivoDeLeitura.read((char *)matrizCaracteres[i], matrizInfo[1]);
    }

    matrizPixels = new int *[matrizInfo[0]];
    for (int i = 0; i < matrizInfo[0]; i++)
    {
        matrizPixels[i] = new int[matrizInfo[1]];
        for (int j = 0; j < matrizInfo[1]; j++)
        {
            matrizPixels[i][j] = (unsigned int)matrizCaracteres[i][j];
        }
        delete[] matrizCaracteres[i];
    }
    delete[] matrizCaracteres;

    arquivoDeLeitura.close();
}

void balanceamentoDosCaracteresPorDensidade(int **&matrizPixels, int matrizInfo[2], char **&caracteresBalanceados)
{
    // Encontro a densidade dos pixels presentes na matriz e atribuo um caractere específico dentro dos intervalos definidos
    caracteresBalanceados = new char *[matrizInfo[0]];
    for (int i = 0; i < matrizInfo[0]; i++)
    {
        caracteresBalanceados[i] = new char[matrizInfo[1]];
        for (int j = 0; j < matrizInfo[1]; j++)
        {
            if (matrizPixels[i][j] <= 24)
            {
                caracteresBalanceados[i][j] = '$';
            }
            else if (matrizPixels[i][j] > 24 && matrizPixels[i][j] <= 48)
            {
                caracteresBalanceados[i][j] = '@';
            }
            else if (matrizPixels[i][j] > 48 && matrizPixels[i][j] <= 72)
            {
                caracteresBalanceados[i][j] = 'B';
            }
            else if (matrizPixels[i][j] > 72 && matrizPixels[i][j] <= 96)
            {
                caracteresBalanceados[i][j] = '%';
            }
            else if (matrizPixels[i][j] > 96 && matrizPixels[i][j] <= 120)
            {
                caracteresBalanceados[i][j] = '8';
            }
            else if (matrizPixels[i][j] > 120 && matrizPixels[i][j] <= 144)
            {
                caracteresBalanceados[i][j] = '&';
            }
            else if (matrizPixels[i][j] > 144 && matrizPixels[i][j] <= 168)
            {
                caracteresBalanceados[i][j] = 'W';
            }
            else if (matrizPixels[i][j] > 168 && matrizPixels[i][j] <= 192)
            {
                caracteresBalanceados[i][j] = 'M';
            }
            else if (matrizPixels[i][j] > 192 && matrizPixels[i][j] <= 216)
            {
                caracteresBalanceados[i][j] = '#';
            }
            else
            {
                caracteresBalanceados[i][j] = '*';
            }
        }
        delete[] matrizPixels[i];
    }
    delete[] matrizPixels;
}

void escreverNoArquivoFinal(char *nomeArquivo, char **&caracteresBalanceados, int matrizInfo[2], char *dimensoesImagem)
{
    ofstream arquivoDeEscrita(nomeArquivo, ios::binary);

    if (!arquivoDeEscrita)
    {
        cerr << "Erro abrindo o arquivo de escrita: " << nomeArquivo << endl;
        exit(-1);
    }

    // Escrevo as dimensões da imagem no arquivo de saída
    arquivoDeEscrita.write((char *)dimensoesImagem, 8);

    // Escrevo a matriz de caracteres balanceados no arquivo de saída
    for (int i = 0; i < matrizInfo[0]; i++)
    {
        arquivoDeEscrita.write(caracteresBalanceados[i], matrizInfo[1]);
        arquivoDeEscrita << endl;
        delete[] caracteresBalanceados[i];
    }
    delete[] caracteresBalanceados;

    arquivoDeEscrita.close();
}

int main(int argc, char *argv[])
{
    int **matrizPixels;
    char **caracteresBalanceados;
    int matrizInfo[2] = {0, 0}; // primeira dimensão é o número de linhas, a segunda é o número de colunas
    char *dimensoesImagem = new char[9];

    ifstream arquivoDeLeitura(argv[1], ios::binary);

    if (!arquivoDeLeitura)
    {
        cerr << "Erro abrindo o arquivo de origem: " << argv[1] << endl;
        exit(-1);
    }

    pegarDimensoesDaImagem(arquivoDeLeitura, matrizInfo);

    lerConteudoDoArquivoOrigem(arquivoDeLeitura, matrizPixels, matrizInfo, dimensoesImagem);

    balanceamentoDosCaracteresPorDensidade(matrizPixels, matrizInfo, caracteresBalanceados);

    escreverNoArquivoFinal(argv[2], caracteresBalanceados, matrizInfo, dimensoesImagem);

    return 0;
}