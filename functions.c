#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include "header.h"

processPlan *inicializarProcessPlan() {
	processPlan *processPlanEmMemoria;
	processPlanEmMemoria = (processPlan *) malloc( sizeof(processPlan));
	
	if(processPlanEmMemoria==NULL) {
		system("cls");
		printf("Nao foi possivel criar nenhum Process Plan\n\n");
		system("pause");
		return(NULL);
	}
	else {
		(*processPlanEmMemoria).nJobs = 0;
		(*processPlanEmMemoria).op = inicializarJob();
		return(processPlanEmMemoria);
	}
}

job *inicializarJob() {
	job *jobEmMemoria;
	jobEmMemoria = (job *) malloc( sizeof(job));
	
	if(jobEmMemoria==NULL) {
		system("cls");
		printf("Nao foi possivel criar a operacao\n\n");
		system("pause");
		return(NULL);
	}
	else {
		(*jobEmMemoria).nOperacoes = 0;
		(*jobEmMemoria).op = IniciarOperacao();
		return(jobEmMemoria);
	}
}

operacao *IniciarOperacao() {
	operacao *operacaoEmMemoria;
	operacaoEmMemoria = (operacao *) malloc( sizeof(operacao));
	
	if(operacaoEmMemoria==NULL) {
		system("cls");
		printf("Nao e possivel criar lista\n\n");
		system("pause");
		return(NULL);
	}
	else {
		(*operacaoEmMemoria).id=0;
		(*operacaoEmMemoria).next=NULL;
		return(operacaoEmMemoria);
	}
}

void menu(int *opcao) {
    int i, success;
	char *endptr, buf[1024];
	
	do {
		system("cls");
		printf("\n");
		_printf_p("           MENU               \n"
				  " 1 - Inserir Operacao         \n"
				  " 2 - Listar Operacoes         \n"
				  " 3 - Remover Operacao         \n"
				  " 4 - Editar Operacao          \n"
				  " 5 - Determinar Menor Tempo   \n"
				  " 6 - Determinar Maior Tempo   \n"
				  " 7 - Determinar Tempo Medio   \n"
				  " 8 - Guardar Dados            \n"
				  " 0 - Sair                     \n");
		
		printf("\n\nOpcao: ",188);

		if (!fgets(buf, sizeof(buf), stdin)) {
			success = 0;
		}
		errno = 0;
		(*opcao) = strtol(buf, &endptr, 10);
		if (errno == ERANGE) {
			printf("Por favor, insire um numero valido.\n\n");
			system("pause");
			success = 0;
		}
		else if (((*opcao) > 8) || ((*opcao) < 0)) {
			printf("Por favor insira um numero entre 0 e 8.\n\n");
			system("pause");
			success = 0;
		}
		else if (endptr == buf)	{
			success = 0;
		}
		else if ((*endptr) && (*endptr != '\n')) {
			success = 0;
		}
		else {
			success = 1;
		}
	}while(!success);
}

void verificarDadosNoFicheiro(operacao *op, int *idCont, int *nOperacoes) {	
	FILE *fileProcessPlan = NULL;
	do
	{
		int jobInt = 0;
		fileProcessPlan = fopen("ProcessPlan"+jobInt+".txt","r");

		operacao *opP; 
		operacao *opEmMem;

		char symb ;
		unsigned char symbI;
		int i = 0; 
		int cont = 0; 
		int success = 0;
		int arrayMaquina[100]; 
		int arrayTempo[100];

		if(fileProcessPlan != NULL) {
			do {
				if((symb = getc(fileProcessPlan)) != EOF) {
					i = cont = 0;
					while ((symb=getc(fileProcessPlan))!='\n') {
						symbI = (int) symb;
						if(symbI >= '0' && symbI <='9') {
							arrayMaquina[i] = symbI - '0';
							cont++;
							i++;
						}
					}
					i=0;
					while ((symb=getc(fileProcessPlan))!='\n') {
						symbI = (int) symb;
						if(symbI >= '0' && symbI <='9') {
							arrayTempo[i] = symbI - '0';
							i++;
						}
					}

					opP=(operacao *)malloc(sizeof(operacao));
					(*opP).next=NULL;

					while((*op).next != NULL) {
						op = (*op).next;
					}

					(*nOperacoes)++;

					(*idCont)++;
					(*op).id = (*idCont);
					(*op).qttMaquinas = cont;
					(*op).MaquinaTempo = (int *)malloc(sizeof(int[2][cont]));

					for(i=0; i < cont; i++) {
						(*op).MaquinaTempo[0*cont + i] = arrayMaquina[i];
						(*op).MaquinaTempo[1*cont + i] = arrayTempo[i];
					}
					(*op).next = opP;
					success = 0;
				}
				else{
					success = 1;
				}
			}while(success == 0);
		}

		fclose(fileProcessPlan);
	}
	while(fileProcessPlan != NULL);
}

void inserirNovaOperacao(operacao *op, int *idCont) {
    char *input;
    int i;
	int j;
	operacao *opEmMem;

	opEmMem = (operacao *)malloc(sizeof(operacao));
	
	system("cls");
	if(opEmMem==NULL) { 
		printf("Nao existe mais espaço na memoria. Elimine uma das maquinas \n\n");
		system("pause");
	}
	else {
		system("cls");
        (*opEmMem).next=NULL;
		while(((*op).next) != NULL) {
			op = (*op).next;
		}

		(*idCont)++;
		(*op).id = (*idCont);

		printf("Quantas maquinas deseja utilizar nesta nova operacao: ");
		fgets(input, sizeof(input), stdin); // 4
		(*op).qttMaquinas = strtol(input, NULL, 0); // 4
		(*op).MaquinaTempo = (int *)malloc(sizeof(int[2][(*op).qttMaquinas])); //[x,y],[x,y],[x,y],[x,y]
		for (i = 0; i <= 1; ++i) {
			for (j = 0; j < (*op).qttMaquinas; ++j) {
				if(i==0) {
					printf("Qual vai ser o id da sua nova maquina na posicao %d: ", j); // 2 4 6 8
					fgets(input, sizeof(input), stdin);
					(*op).MaquinaTempo[i*(*op).qttMaquinas + j] = strtol(input, NULL, 10);
				}
				else {
					printf("Qual o tempo que a maquina: %d vai precisar: ", (*op).MaquinaTempo[0*(*op).qttMaquinas + j]); // 10 4 7 9  
					fgets(input, sizeof(input), stdin);
					(*op).MaquinaTempo[i*(*op).qttMaquinas + j] = strtol(input, NULL, 10);
				}
			}
		}
		(*op).next = opEmMem;
	}
}

void listaOperacoes(operacao *op, int nOperacoes) {
	int i = 0;
	int j = 0;	

	system("cls");
	if((*op).next==NULL)	{
		puts("Nenhum");
	}
	else {
		printf("Este Plan tem: %d Operacoes\n", nOperacoes);
		while((*op).next != NULL) {
			printf("Id - (%d)\n",(*op).id);
			printf("Maquinas - (");
			for (j = 0; j < (*op).qttMaquinas; ++j) {
				if(((*op).qttMaquinas - j) == 1) // 4(4 Maquinas) - 3(Posicao j que é a ultima posição) = 1
					printf("%d",(*op).MaquinaTempo[0*(*op).qttMaquinas + j]);
				else
					printf("%d,",(*op).MaquinaTempo[0*(*op).qttMaquinas + j]);
			}
			printf(")\nTempo - (");
			for (j = 0; j < (*op).qttMaquinas; ++j) {
				if(((*op).qttMaquinas - j) == 1)
					printf("%d",(*op).MaquinaTempo[1*(*op).qttMaquinas + j]);
				else
					printf("%d,",(*op).MaquinaTempo[1*(*op).qttMaquinas + j]);	
			}
			printf(")\n\n");
			op=(*op).next;
		}
	}
	printf("\n\n");
	system("pause");
}

void removeOperacao(job **jobList) {
	operacao *y, *anterior, *seguinte, *opEmMem;
	int j; 
	int idRetirar;
	char elemRetirar[40];

	system("cls");
	y=(*jobList)->op;
	
	if(((*y).next)==NULL) { 
		printf("A lista nao tem dados"); 
	}
	
	else {
		printf("Diga o id que deseja que seja retirado?\n");
		if(fgets(elemRetirar, sizeof(elemRetirar), stdin)) {
			elemRetirar[strcspn(elemRetirar, "\n")] = 0;
			idRetirar = strtol(elemRetirar, NULL, 0);
		}

		if(idRetirar == (*(*jobList)->op).id) {
			system ("cls");
			printf("O elemento foi retirado\n");
			printf("Id - (%d)\n",(*(*jobList)->op).id);
			printf("Ainda existem: (%d) Maquinas - (",(*(*jobList)->op).qttMaquinas);
			for (j = 0; j < (*(*jobList)->op).qttMaquinas; ++j) {
				if(((*(*jobList)->op).qttMaquinas - j) == 1)
					printf("%d",(*(*jobList)->op).MaquinaTempo[0*(*(*jobList)->op).qttMaquinas + j]);
				else
					printf("%d,",(*(*jobList)->op).MaquinaTempo[0*(*(*jobList)->op).qttMaquinas + j]);
			}
			printf(")\nTempo - (");
			for (j = 0; j < (*(*jobList)->op).qttMaquinas; ++j) {
				if(((*(*jobList)->op).qttMaquinas - j) == 1)
					printf("%d",(*(*jobList)->op).MaquinaTempo[1*(*(*jobList)->op).qttMaquinas + j]);
				else
					printf("%d,",(*(*jobList)->op).MaquinaTempo[1*(*(*jobList)->op).qttMaquinas + j]);
			}
			printf(")\n");
			system("pause");
			(*jobList)->op=(*(*jobList)->op).next;
			free(y);
		}
		else {
			opEmMem=(*jobList)->op;
			while((idRetirar != (*opEmMem).id) && ((*(*opEmMem).next).next!=NULL)) {
				anterior=opEmMem;
				opEmMem=(*opEmMem).next;
				seguinte=(*opEmMem).next;
			}
			
			if(idRetirar == (*opEmMem).id) {
				(*anterior).next=seguinte;
				system ("cls");
				printf("A Operacao foi eliminada\n");
				printf("Id - (%d)\n",(*opEmMem).id);
				printf("Operacao - (");
				for (j = 0; j < (*opEmMem).qttMaquinas; ++j) {
					if(((*opEmMem).qttMaquinas - j) == 1)
						printf("%d",(*opEmMem).MaquinaTempo[0*(*opEmMem).qttMaquinas + j]);
					else
						printf("%d,",(*opEmMem).MaquinaTempo[0*(*opEmMem).qttMaquinas + j]);
				}
				printf(")\nTime - (");
				for (j = 0; j < (*opEmMem).qttMaquinas; ++j) {
					if(((*opEmMem).qttMaquinas - j) == 1)
						printf("%d",(*opEmMem).MaquinaTempo[1*(*opEmMem).qttMaquinas + j]);
					else
						printf("%d,",(*opEmMem).MaquinaTempo[1*(*opEmMem).qttMaquinas + j]);
				}
				printf(")\n");
				system("pause");
				free(opEmMem);
			}
			else {
				system("cls"); 
				printf("A operacao com o id %s foi eliminada da lista", elemRetirar);
			}
		}
	}
}

void editarOperacao(operacao *operacaoLista) {
	operacao *opEmMem;
	int i;
	int j;
	int idEditar;
	char elemEditar[40], *input;

	system("cls");
	
	if(((*operacaoLista).next)==NULL) { 
		printf("A lista nao tem dados"); 
	}
	else {
		printf("Diga o id da operacao que deseja editar?\n");
		if(fgets(elemEditar, sizeof(elemEditar), stdin)) {
			elemEditar[strcspn(elemEditar, "\n")] = 0;
			idEditar = strtol(elemEditar, NULL, 0);
		}

		if(idEditar == (*operacaoLista).id) {
			system ("cls");
			printf("A operacao a editar\n");
			printf("Id - (%d)\n",(*operacaoLista).id);
			printf("Maquina Quantidade - (%d)\nMaquina - (",(*operacaoLista).qttMaquinas);
			for (j = 0; j < (*operacaoLista).qttMaquinas; ++j) {
				if(((*operacaoLista).qttMaquinas - j) == 1)
					printf("%d",(*operacaoLista).MaquinaTempo[0*(*operacaoLista).qttMaquinas + j]);
				else
					printf("%d,",(*operacaoLista).MaquinaTempo[0*(*operacaoLista).qttMaquinas + j]);
			}
			printf(")\nTempo - (");
			for (j = 0; j < (*operacaoLista).qttMaquinas; ++j) {
				if(((*operacaoLista).qttMaquinas - j) == 1)
					printf("%d",(*operacaoLista).MaquinaTempo[1*(*operacaoLista).qttMaquinas + j]);
				else
					printf("%d,",(*operacaoLista).MaquinaTempo[1*(*operacaoLista).qttMaquinas + j]);
			}
			printf(")\n\n");
			free((*operacaoLista).MaquinaTempo);

			printf("Quantas maquinas deseja utilizadar para esta operacao: ");
			fgets(input, sizeof(input), stdin);
			(*operacaoLista).qttMaquinas = strtol(input, NULL, 0);
			(*operacaoLista).MaquinaTempo = (int *)malloc(sizeof(int[2][(*operacaoLista).qttMaquinas]));
			for (i = 0; i < 2; ++i) {
				for (j = 0; j < (*operacaoLista).qttMaquinas; ++j) {
					if(i==0) {
						printf("Qual o id da maquina que pretende utilizar: ");
						fgets(input, sizeof(input), stdin);
						(*operacaoLista).MaquinaTempo[i*(*operacaoLista).qttMaquinas + j] = strtol(input, NULL, 10);
					}
					else {
						printf("Qual o tempo que a maquina: %d vai demorar: ", (*operacaoLista).MaquinaTempo[0*(*operacaoLista).qttMaquinas + j]);
						fgets(input, sizeof(input), stdin);
						(*operacaoLista).MaquinaTempo[i*(*operacaoLista).qttMaquinas + j] = strtol(input, NULL, 10);
					}
				}
			}
		}
		else {
			opEmMem=operacaoLista;
			while((idEditar != (*operacaoLista).id) && (*operacaoLista).next != NULL) {
				operacaoLista = (*operacaoLista).next;
			}
			
			if(idEditar == (*operacaoLista).id) {
				system ("cls");
				printf("O elemento a editar\n");
				printf("Id - (%d)\n",(*operacaoLista).id);
				printf("Maquina Quantidade - (%d)\nMaquina - (",(*operacaoLista).qttMaquinas);
				for (j = 0; j < (*operacaoLista).qttMaquinas; ++j) {
					if(((*operacaoLista).qttMaquinas - j) == 1)
						printf("%d",(*operacaoLista).MaquinaTempo[0*(*operacaoLista).qttMaquinas + j]);
					else
						printf("%d,",(*operacaoLista).MaquinaTempo[0*(*operacaoLista).qttMaquinas + j]);
				}
				printf(")\nTempo - (");
				for (j = 0; j < (*operacaoLista).qttMaquinas; ++j) {
					if(((*operacaoLista).qttMaquinas - j) == 1)
						printf("%d",(*operacaoLista).MaquinaTempo[1*(*operacaoLista).qttMaquinas + j]);
					else
						printf("%d,",(*operacaoLista).MaquinaTempo[1*(*operacaoLista).qttMaquinas + j]);
				}
				printf(")\n\n");
				free((*operacaoLista).MaquinaTempo);

				printf("Quantas maquinas deseja utilizadar para esta operacao: ");
				fgets(input, sizeof(input), stdin);
				(*operacaoLista).qttMaquinas = strtol(input, NULL, 0);
				(*operacaoLista).MaquinaTempo = (int *)malloc(sizeof(int[2][(*operacaoLista).qttMaquinas]));
				for (i = 0; i < 2; ++i) {
					for (j = 0; j < (*operacaoLista).qttMaquinas; ++j) {
						if(i==0) {
							printf("Qual o id da maquina que pretende utilizar: ");
							fgets(input, sizeof(input), stdin);
							(*operacaoLista).MaquinaTempo[i*(*operacaoLista).qttMaquinas + j] = strtol(input, NULL, 10);
						}
						else {
							printf("Qual o tempo que a maquina: %d vai demorar: ", (*operacaoLista).MaquinaTempo[0*(*operacaoLista).qttMaquinas + j]);
							fgets(input, sizeof(input), stdin);
							(*operacaoLista).MaquinaTempo[i*(*operacaoLista).qttMaquinas + j] = strtol(input, NULL, 10);
						}
					}
				}
				operacaoLista = opEmMem;
			}
			else {
				system("cls"); 
				printf("A operacao com o id: %s nao existe na lista", elemEditar);
			}
		}
	}
}

void determineTempoMaisCurto(operacao *op) {
	int i = 0;
	int j = 0; 
	int soma = 0; 
	int min;
	int minTemporario;

	system("cls");
	if((*op).next==NULL) {
		puts("Nenhum dado");
	}
	else {
		printf("Quantidade minima de tempo necessario para completar as operacoes por ordem:\n");
		while((*op).next != NULL) { 
			min = 99999;
			for (j = 0; j < (*op).qttMaquinas; ++j) {
				if((*op).MaquinaTempo[1*(*op).qttMaquinas + j] < min) {
					min = (*op).MaquinaTempo[1*(*op).qttMaquinas + j];
					minTemporario = (*op).MaquinaTempo[0*(*op).qttMaquinas + j];
				}
			}
			printf("%d", minTemporario);
			if((*(*op).next).next != NULL)
				printf("-");

			soma = soma + min;
			op=(*op).next;
		}
		printf("\nTempo total: %d", soma);
	}
	printf("\n\n");
	system("pause");
}

void determineTempoMaisLongo(operacao *op) {
	int i = 0;
	int j = 0; 
	int soma = 0; 
	int max;
	int maxTemporario;

	system("cls");
	if((*op).next==NULL) {
		puts("Nenhum dado");
	}
	else {
		printf("Quantidade maxima de tempo necessario para completar as operacoes por ordem:\n");
		while((*op).next != NULL) { 
			max = 0;
			for (j = 0; j < (*op).qttMaquinas; ++j) {
				if((*op).MaquinaTempo[1*(*op).qttMaquinas + j] > max) {
					max = (*op).MaquinaTempo[1*(*op).qttMaquinas + j];
					maxTemporario = (*op).MaquinaTempo[0*(*op).qttMaquinas + j];
				}
			}
			printf("%d", maxTemporario);
			if((*(*op).next).next != NULL)
				printf("-");

			soma = soma + max;
			op=(*op).next;
		}
		printf("\nTempo total: %d", soma);
	}
	printf("\n\n");
	system("pause");
}

void determineTempoMedio(operacao *op) {
	int i = 0;
	int j = 0;
	int  max;
	float soma = 0;
	float proc = 0;

	system("cls");
	if((*op).next==NULL) {
		puts("Nenhum dado");
	}
	else {
		printf("Media de unidades de tempo necessarias para completar as operacoes de cada maquina:\n");
		while((*op).next != NULL) { 
			soma = 0;
			proc = 0;
			for (j = 0; j < (*op).qttMaquinas; ++j) {
				soma = soma + (*op).MaquinaTempo[1*(*op).qttMaquinas + j];
				proc = proc + 1;
			}
			printf("Media Operacao Id-(%d):",(*op).id);
			float result = (soma / proc);			
			printf("%.2f", result);
			printf("\n");
			if((*(*op).next).next != NULL)
				printf("\n");

			op=(*op).next;
		}
	}
	printf("\n\n");
	system("pause");
}
void guardarDados(job *jobs, int nJobs,operacao *op, int nOperacoes) {
	int i = 0;
	int j = 0;
	int y = 0;	

	system("cls");
	if((*jobs.next == NULL))
	{
				puts("Nenhum");
	}else{
		if((*op).next==NULL)
		{
			puts("Nenhum");
		}
		else 
		{
			do{
				FILE *fileWritter = fopen("ProcessPlan"+y+".txt", "w");
				if (fileWritter == NULL)
				{
					printf("Erro ao abrir ficheiro!\n");
					exit(1);
				}
				printf("A escrever no ficheiro %d operações\n", nOperacoes);
				while((*op).next != NULL) {
					
					fprintf(fileWritter,"(");
					for (j = 0; j < (*op).qttMaquinas; ++j) {
						if(((*op).qttMaquinas - j) == 1)
							fprintf(fileWritter,"%d",(*op).MaquinaTempo[0*(*op).qttMaquinas + j]);
						else
							fprintf(fileWritter,"%d,",(*op).MaquinaTempo[0*(*op).qttMaquinas + j]);
					}
					fprintf(fileWritter,")\n[");
					for (j = 0; j < (*op).qttMaquinas; ++j) {
						if(((*op).qttMaquinas - j) == 1)
							fprintf(fileWritter,"%d",(*op).MaquinaTempo[1*(*op).qttMaquinas + j]);
						else
							fprintf(fileWritter,"%d,",(*op).MaquinaTempo[1*(*op).qttMaquinas + j]);
					}
					fprintf(fileWritter,"]\n");
					op=(*op).next;
				}
				fclose(fileWritter);
				y = y + 1;
			}while(y != nJobs);


		}
		printf("\n\n");
		system("pause");
	}


}


