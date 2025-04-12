#include <conio2.h>
#include <stdio.h>

#define MAXFILA 100

struct Tarefa{
    int Id, status;
    char Nome[200], Data[20];
};

struct Fila{
    int Inicio, Fim, Quantidade;
    Tarefa Fila[MAXFILA];
};

void Inserir(Fila &FC, Tarefa Elem)
{
    if(FC.Fim == MAXFILA)
        FC.FIm--;
    
    FC.Fila[FC.++Fim] = Elem;
    FC.Quantidade++;
}

Tarefa Retirar(Fila &FC)
{
    Tarefa Aux = FC.Fila[FC.Inicio++];

    if(FC.Inicio == MAXFILA)
        FC.Inicio = 0;
    
    FC.Quantidade--;
    return Aux;
}

char Vazio(int Quantidade)
{
    return Quantidade == 0;
}

char Cheio(int Quantidade)
{
    return Quantidade == MAXFILA;
}

void Exibir(Fila FC)
{
    Tarefa Aux;

    while(!Vazio(FC))
    {
        Aux = Retirar(FC);
        printf("%s", Aux.Nome);
        printf(" %s", Aux.Data);
    }
}