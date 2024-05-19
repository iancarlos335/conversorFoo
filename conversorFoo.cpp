/*
    2212006 - Ian Carlos Azevedo Martins
    2231823 - Nicole Santarosa de Luca
    2223579 - Rafael Calixto Avelar Marcelino
*/
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string nomeArquivo = "exemplos/img0.foo";
    char character;

    ifstream leituraArquivo(nomeArquivo, ios::in);

    while (leituraArquivo >> character)
    {
        cout << character;
    }

    leituraArquivo.close();
    return 0;
}