struct Tarefa
{
    int status, prioridade;
    char desc[100], data[10];
};

struct Tarefas
{
    int local, prioridade;
    Tarefas *prox, *ant;
};

struct TarefasC
{
    int local, prioridade;
    TarefasC *prox, *ant;
};

void read(Tarefas *Inicio, TarefasC *InicioC)
{
    int pos;
    Tarefa AuxT;

    Inicio -> prox = Inicio -> ant = NULL;
    InicioC -> prox = InicioC -> ant = NULL;

    FILE *Ptr = fopen("Tarefas.dat","rb");

    if(!feof(Ptr))
    {
        pos = ftell(Ptr);
        fread(&AuxT,sizeof(Tarefa),1,Ptr);
        
        do
        {
            if(AuxT.status == 0)
            {
                Tarefas *Aux = new Tarefas;

                Aux -> local = pos;
                Aux -> prioridade = AuxT.prioridade;
                Aux -> ant = Aux -> prox = NULL;
 
                if(Inicio -> prox == NULL)
                    Inicio -> prox = Aux;
                else if(Inicio -> prox -> prioridade > AuxT.prioridade)
                {
                    Aux -> prox = Inicio -> prox;
                    Inicio -> prox -> ant = Aux;
                    Inicio -> prox = Aux;
                }
                else
                {
                    Aux -> prox = Inicio -> prox;

                    while(Aux -> prox -> prox != NULL && Aux -> prox -> prioridade <= AuxT.prioridade)
                        Aux -> prox = Aux -> prox -> prox;

                    if(Aux -> prox -> prioridade > AuxT.prioridade)
                    {
                        Aux -> ant = Aux -> prox -> ant;
                        Aux -> prox -> ant = Aux -> prox -> ant -> prox = Aux;
                    }
                    else
                    {
                        Aux -> prox -> prox = Aux;
                        Aux -> ant = Aux -> prox;
                        Aux -> prox = NULL;
                    }
                }
            }
            else
            {
                TarefasC *AuxC = new TarefasC;

                AuxC -> local = pos;
                AuxC -> prioridade = AuxT.prioridade;
                AuxC -> ant = AuxC -> prox = NULL;

                if(InicioC -> prox == NULL)
                    InicioC -> prox = AuxC;
                else if(InicioC -> prox -> prioridade > AuxT.prioridade)
                {
                    AuxC -> prox = InicioC -> prox;
                    InicioC -> prox -> ant = AuxC;
                    InicioC -> prox = AuxC;
                }
                else
                {
                    AuxC -> prox = InicioC -> prox;

                    while(AuxC -> prox -> prox != NULL && AuxC -> prox -> prioridade <= AuxT.prioridade)
                        AuxC -> prox = AuxC -> prox -> prox;

                    if(AuxC -> prox -> prioridade > AuxT.prioridade)
                    {
                        AuxC -> ant = AuxC -> prox -> ant;
                        AuxC -> prox -> ant = AuxC -> prox -> ant -> prox = AuxC;
                    }
                    else
                    {
                        AuxC -> prox -> prox = AuxC;
                        AuxC -> ant = AuxC -> prox;
                        AuxC -> prox = NULL;
                    }
                }
            }

            pos = ftell(Ptr);
            fread(&AuxT,sizeof(Tarefa),1,Ptr);

        }while(!feof(Ptr));
    }
    fclose(Ptr);
}

void store(Tarefas *Inicio, TarefasC *InicioC)
{
    int num;
    char Aux[30];
    Tarefa AuxT;

    clrscr();
    gotoxy(0,0);
    printf("Digite a data da Tarefa: ");
    scanf(" %s",AuxT.data);

    clrscr();
    gotoxy(0,0);
    printf("Digite a data da Tarefa: %s\n", AuxT.data);
    printf("Digite a descricao da Tarefa: ");
    scanf(" %s",AuxT.desc);
    
    do
    {
        clrscr();
        gotoxy(0,0);
        printf("Digite a data da Tarefa: %s\n", AuxT.data);
        printf("Digite a descricao da Tarefa: %s\n", AuxT.desc);
        printf("[1] - Alta\n");
        printf("[2] - Media\n");
        printf("[3] - Baixa\n");
        printf("Selecione a prioridade da Tarefa: ");
        scanf(" %d", &AuxT.prioridade);
    } while (AuxT.prioridade < 1 || AuxT.prioridade > 3);

    switch (AuxT.prioridade)
    {
        case 1:
            strcpy(Aux,"Alta");
        break;

        case 2:
            strcpy(Aux,"Media");
        break;

        case 3:
            strcpy(Aux,"Baixa");
        break;
    }

    char Op;

    do
    {
        clrscr();
        gotoxy(0,0);
        printf("Data da Tarefa: %s\n", AuxT.data);
        printf("Descricao da Tarefa: %s\n", AuxT.desc);
        printf("Prioridade da Tarefa: %s\n", Aux);
        printf("Confirme o Cadastro(y/n): ");
        Op = toupper(getch());
    } while(Op != 'Y' && Op != 'N');

    AuxT.status = 1;

    FILE *Ptr = fopen("Tarefas.dat","ab");

    fwrite(&AuxT,sizeof(Tarefa),1,Ptr);

    fclose(Ptr);

    clrscr();
    gotoxy(0,0);
    printf("Tarefa Cadastrada com sucesso", AuxT.data);

    getch();
    
}
