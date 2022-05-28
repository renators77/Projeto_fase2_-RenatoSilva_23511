#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#include "header.h"
#include "functions.c"

int main(int argc, char const *argv[]) {
    
    job *jobList;
    //processPlan *processPlanList;

    int opcao; 
    int idCont = 0;
    //processList = inicializarProcessPlan();
    
    jobList = inicializarJob();
	verificarDadosNoFicheiro(jobList->op,&idCont,&(jobList->nOperacoes));

    do {
        menu(&opcao);

        switch(opcao) {
            case 0: printf("terminado!!\n\n"); 
					break;
            case 1: inserirNovaOperacao(jobList->op,&idCont); 
					break;
            case 2: listaOperacoes(jobList->op,jobList->nOperacoes); 
					break;
            case 3: removeOperacao(&jobList);
					break;
            case 4: editarOperacao(jobList->op);
					break;
            case 5: determineTempoMaisCurto(jobList->op);
					break;
            case 6: determineTempoMaisLongo(jobList->op);
					break;
            case 7: determineTempoMedio(jobList->op);
            		break;
            case 8: guardarDados(jobList->op,jobList->nOperacoes); 
					break;
        }
    }while(opcao != 0);

    free(jobList->op);
    free(jobList);
    return 0;
}