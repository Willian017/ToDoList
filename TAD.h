struct Tarefa
{
    int status, prioridade;
    char desc[100], data[10];
};

struct Tarefas
{
    int local;
    Tarefas *prox, *ant;
};

struct TarefasC
{
    int local;
    TarefasC *prox, *ant;
};

void Read(Tarefas *Inicio, TarefasC *InicioC)
{
    int pos;
    Tarefa AuxT;

    Inicio -> prox = Inicio -> ant = NULL;
    InicioC -> prox = InicioC -> ant = NULL;

    FILE *Ptr = fopen("rb+","Tarefas.txt");

    if(!feof(Ptr))
    {
        pos = fseek(Ptr,,Aux);
        Tarefas *Aux;
        TarefasC *AuxC;

        do
        {
            if(AuxT.status == 0)
            {
                if(Inicio -> prox == NULL)
                {
                    Aux -> local = pos;
                    Inicio -> prox = Aux;
                    Aux -> ant = Aux -> prox = NULL;
                }
            }
            else
            {
                if(InicioC -> prox == NULL)
                {
                    Aux -> local = pos;
                    InicioC -> prox = Aux;
                    Aux -> ant = Aux -> prox = NULL;
                }
            }

            fread(Ptr,,Aux);
        }while(!feof(Ptr));
    }
}