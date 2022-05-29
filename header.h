#ifndef DATA
#define DATA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#pragma region Structs 

//-------------------------------------------------------
typedef struct operacao {
    int id;
    int njob;
    int qttMaquinas;
    int *MaquinaTempo;
    struct operacao *next;
}operacao;
//-------------------------------------------------------
typedef struct job {
    int id;
    int nOperacoes;
    operacao *op;
    
}job;
//-------------------------------------------------------
typedef struct processPlan {

    int nJobs;
    struct job *allJobs;
    
}processPlan;

#pragma endregion
//#####################################################################################################
//#####################################################################################################
#pragma region Signatures
processPlan *inicializarProcessPlan();
job *inicializarJob();
operacao *IniciarOperacao();
void verificarDadosNoFicheiro(operacao *op, int *idCont, int *nOperacoes);
void menu(int *opcao);
void inserirNovaOperacao(operacao *op, int *idCont);
void listaOperacoes(operacao *op, int nOperacoes);
void removeOperacao(job **jobList);
void editarOperacao(operacao *op);
void determineTempoMaisCurto(operacao *op);
void determineTempoMaisLongo(operacao *op);
void determineTempoMedio(operacao *op);
void guardarDados(operacao *op, int nOperacoes);
void InserirJob (processPlan *pPlan, int *idJob);
void RemoverJobOperacao (job **jobList);
void EditarJob(operacao *operacaoLista);

#pragma endregion

#endif