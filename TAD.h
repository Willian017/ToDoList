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

void Read(Tarefas *Inicio, TarefasC *InicioC)
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
                else if(Inicio -> prox -> prioridade < AuxT.prioridade)
                {
                    Aux -> prox = Inicio -> prox;
                    Inicio -> prox -> ant = Aux;
                    Inicio -> prox = Aux;
                }
                else
                {
                    Aux -> prox = Inicio -> prox;

                    while(Aux -> prox -> prox != NULL && Aux -> prox -> prioridade >= AuxT.prioridade)
                        Aux -> prox = Aux -> prox -> prox;

                    if(Aux -> prox -> prioridade < AuxT.prioridade)
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
                else if(InicioC -> prox -> prioridade < AuxT.prioridade)
                {
                    AuxC -> prox = InicioC -> prox;
                    InicioC -> prox -> ant = AuxC;
                    InicioC -> prox = AuxC;
                }
                else
                {
                    AuxC -> prox = InicioC -> prox;

                    while(AuxC -> prox -> prox != NULL && AuxC -> prox -> prioridade >= AuxT.prioridade)
                        AuxC -> prox = AuxC -> prox -> prox;

                    if(AuxC -> prox -> prioridade < AuxT.prioridade)
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
