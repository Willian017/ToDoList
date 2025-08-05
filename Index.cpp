#include <conio2.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "TAD.h"
#include "Menu.h"

int main()
{
	Tarefas *PTarefas = new Tarefas;
	
	read(PTarefas);
	destroy(PTarefas);
	//show(PTarefas);
	//store(PTarefas);
}
