struct Tarefa
{
    int status, prioridade;
    char desc[100], data[10];
};

struct Tarefas
{
    int local, prioridade, status;
    Tarefas *prox, *ant;
};

void read(Tarefas *Inicio)
{
    int pos;
    Tarefa AuxT;

    Inicio -> prox = Inicio -> ant = NULL;

    FILE *Ptr = fopen("Tarefas.dat","rb");

    if(!feof(Ptr))
    {
        pos = ftell(Ptr);
        fread(&AuxT,sizeof(Tarefa),1,Ptr);
        
        do
        {
            Tarefas *Aux = new Tarefas;

            Aux -> local = pos;
            Aux -> prioridade = AuxT.prioridade;
            Aux -> status = AuxT.status;
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

            pos = ftell(Ptr);
            fread(&AuxT,sizeof(Tarefa),1,Ptr);
        }while(!feof(Ptr));
    }

    fclose(Ptr);
}

void store(Tarefas *Inicio)
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

void show(Tarefas *Inicio)
{
    FILE *Ptr = fopen("Tarefas.dat","ab+");
    
    if(Ptr != NULL)
    {
        clrscr();
        printf("Tarefas Ativas: \n");

        if(Inicio -> prox != NULL)
        {
            Tarefa AuxT;
            Tarefas *Aux = Inicio;
            do
            {
                Aux = Aux->prox;
                if(Aux->status == 1)
                {
                    fseek(Ptr,Aux->local,SEEK_SET);
                    fread(&AuxT,sizeof(Tarefa),1,Ptr);
                    printf("%s %s %d\n", AuxT.data, AuxT.desc, AuxT.prioridade);
                }
                
            } while(Aux->prox!=NULL);

            Aux = Inicio;
            printf("\nTarefas Finalizadas: \n");
            do
            {
                Aux = Aux->prox;
                if(Aux->status == 0)
                {
                    fseek(Ptr,Aux->local,SEEK_SET);
                    fread(&AuxT,sizeof(Tarefa),1,Ptr);
                    printf("%s %s %d\n", AuxT.data, AuxT.desc, AuxT.prioridade);
                }
                
            } while(Aux->prox!=NULL);

            delete Aux;
        }
    }

    getch();
    fclose(Ptr);
}
