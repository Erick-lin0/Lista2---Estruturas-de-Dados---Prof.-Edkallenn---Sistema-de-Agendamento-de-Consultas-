/*
** Fun��o : Sistema de Agendamento de Consultas M�dicas
** Autor : Erick e Daysila
** Data : 18/06/2025
** Observa��es: Implementa��o do sistema de agendamento
*/

#include "agendamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========== IMPLEMENTA��O FILA EST�TICA M�DICO ==========

FilaMedico* criarFilaMedico() {
    FilaMedico *fila = (FilaMedico*)malloc(sizeof(FilaMedico));
    if (fila == NULL) {
        printf("Erro: N�o foi poss�vel alocar mem�ria para fila do m�dico.\n");
        return NULL;
    }
    
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
    
    return fila;
}

int filaCheiaMedico(FilaMedico *fila) {
    return fila->tamanho == MAX_MEDICO;
}

int filaVaziaMedico(FilaMedico *fila) {
    return fila->tamanho == 0;
}

int agendarMedico(FilaMedico *fila, char *nome, char *data, char *hora) {
    if (filaCheiaMedico(fila)) {
        printf("ATEN��O: M�dico j� tem 5 consultas agendadas para hoje!\n");
        printf("N�o � poss�vel agendar mais consultas.\n");
        return 0;
    }
    
    fila->fim = (fila->fim + 1) % MAX_MEDICO;
    strcpy(fila->pacientes[fila->fim].nome, nome);
    strcpy(fila->pacientes[fila->fim].data, data);
    strcpy(fila->pacientes[fila->fim].hora, hora);
    fila->tamanho++;
    
    printf("? Consulta agendada com M�DICO!\n");
    printf("Paciente: %s | Data: %s | Hora: %s\n", nome, data, hora);
    printf("Posi��o na fila: %d\n", fila->tamanho);
    
    return 1;
}

int atenderMedico(FilaMedico *fila) {
    if (filaVaziaMedico(fila)) {
        printf("N�o h� pacientes agendados com o m�dico.\n");
        return 0;
    }
    
    Paciente paciente = fila->pacientes[fila->inicio];
    printf(">>> ATENDENDO PACIENTE DO M�DICO <<<\n");
    printf("Paciente: %s\n", paciente.nome);
    printf("Data: %s | Hora: %s\n", paciente.data, paciente.hora);
    
    fila->inicio = (fila->inicio + 1) % MAX_MEDICO;
    fila->tamanho--;
    
    printf("Paciente atendido com sucesso!\n");
    return 1;
}

void listarAgendamentosMedico(FilaMedico *fila) {
    printf("\n=== AGENDAMENTOS DO M�DICO ===\n");
    
    if (filaVaziaMedico(fila)) {
        printf("Nenhum agendamento para o m�dico.\n");
        return;
    }
    
    printf("Total de agendamentos: %d/%d\n", fila->tamanho, MAX_MEDICO);
    printf("----------------------------------------\n");
    
    int pos = fila->inicio;
    for (int i = 0; i < fila->tamanho; i++) {
        printf("%d. %s - %s �s %s\n", 
            i + 1,
            fila->pacientes[pos].nome,
            fila->pacientes[pos].data,
            fila->pacientes[pos].hora);
        pos = (pos + 1) % MAX_MEDICO;
    }
    printf("----------------------------------------\n");
}

void liberarFilaMedico(FilaMedico *fila) {
    if (fila != NULL) {
        free(fila);
    }
}

// ========== IMPLEMENTA��O FILA DIN�MICA ENFERMAGEM ==========

FilaEnfermagem* criarFilaEnfermagem() {
    FilaEnfermagem *fila = (FilaEnfermagem*)malloc(sizeof(FilaEnfermagem));
    if (fila == NULL) {
        printf("Erro: N�o foi poss�vel alocar mem�ria para fila da enfermagem.\n");
        return NULL;
    }
    
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    
    return fila;
}

int filaVaziaEnfermagem(FilaEnfermagem *fila) {
    return fila->inicio == NULL;
}

int agendarEnfermagem(FilaEnfermagem *fila, char *nome, char *data, char *hora) {
    NoEnfermagem *novoNo = (NoEnfermagem*)malloc(sizeof(NoEnfermagem));
    if (novoNo == NULL) {
        printf("Erro: N�o foi poss�vel alocar mem�ria para novo agendamento.\n");
        return 0;
    }
    
    strcpy(novoNo->paciente.nome, nome);
    strcpy(novoNo->paciente.data, data);
    strcpy(novoNo->paciente.hora, hora);
    novoNo->proximo = NULL;
    
    if (filaVaziaEnfermagem(fila)) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->proximo = novoNo;
        fila->fim = novoNo;
    }
    
    fila->tamanho++;
    
    printf("? Consulta agendada com ENFERMAGEM!\n");
    printf("Paciente: %s | Data: %s | Hora: %s\n", nome, data, hora);
    printf("Posi��o na fila: %d\n", fila->tamanho);
    printf("(Enfermagem atende 24h, sem limite de agendamentos)\n");
    
    return 1;
}

int atenderEnfermagem(FilaEnfermagem *fila) {
    if (filaVaziaEnfermagem(fila)) {
        printf("N�o h� pacientes agendados com a enfermagem.\n");
        return 0;
    }
    
    NoEnfermagem *pacienteAtual = fila->inicio;
    
    printf(">>> ATENDENDO PACIENTE DA ENFERMAGEM <<<\n");
    printf("Paciente: %s\n", pacienteAtual->paciente.nome);
    printf("Data: %s | Hora: %s\n", 
        pacienteAtual->paciente.data, 
        pacienteAtual->paciente.hora);
    
    fila->inicio = pacienteAtual->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    
    free(pacienteAtual);
    fila->tamanho--;
    
    printf("Paciente atendido com sucesso!\n");
    return 1;
}

void listarAgendamentosEnfermagem(FilaEnfermagem *fila) {
    printf("\n=== AGENDAMENTOS DA ENFERMAGEM ===\n");
    
    if (filaVaziaEnfermagem(fila)) {
        printf("Nenhum agendamento para a enfermagem.\n");
        return;
    }
    
    printf("Total de agendamentos: %d (sem limite)\n", fila->tamanho);
    printf("Atendimento 24 horas\n");
    printf("----------------------------------------\n");
    
    NoEnfermagem *atual = fila->inicio;
    int contador = 1;
    
    while (atual != NULL) {
        printf("%d. %s - %s �s %s\n", 
            contador,
            atual->paciente.nome,
            atual->paciente.data,
            atual->paciente.hora);
        atual = atual->proximo;
        contador++;
    }
    printf("----------------------------------------\n");
}

void liberarFilaEnfermagem(FilaEnfermagem *fila) {
    if (fila == NULL) return;
    
    NoEnfermagem *atual = fila->inicio;
    while (atual != NULL) {
        NoEnfermagem *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    free(fila);
}

// ========== FUN��ES UTILIT�RIAS ==========

void mostrarStatusFilas(FilaMedico *filaMedico, FilaEnfermagem *filaEnfermagem) {
    printf("\n=== STATUS DAS FILAS DE AGENDAMENTO ===\n");
    printf("----------------------------------------\n");
    printf("M�DICO:\n");
    printf("  Agendamentos: %d/%d\n", filaMedico->tamanho, MAX_MEDICO);
    printf("  Status: %s\n", filaCheiaMedico(filaMedico) ? "LOTADO" : "Dispon�vel");
    printf("  Limite: 5 pacientes por dia\n\n");
    
    printf("ENFERMAGEM:\n");
    printf("  Agendamentos: %d\n", filaEnfermagem->tamanho);
    printf("  Status: Sempre dispon�vel\n");
    printf("  Atendimento: 24 horas, sem limite\n");
    printf("----------------------------------------\n");
}

