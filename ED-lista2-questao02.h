
/*
** Fun��o : Sistema de Agendamento de Consultas M�dicas
** Autor : Erick e Daysila
** Data : 18/06/2025
** Observa��es: Interface do sistema de agendamento
*/

#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#define MAX_NOME 100
#define MAX_DATA 15
#define MAX_HORA 10
#define MAX_MEDICO 5  // Limite de 5 pacientes por dia para m�dico

// Estrutura para representar um paciente
typedef struct {
    char nome[MAX_NOME];
    char data[MAX_DATA];
    char hora[MAX_HORA];
} Paciente;

// Fila Est�tica para M�dico (m�ximo 5 pacientes)
typedef struct {
    Paciente pacientes[MAX_MEDICO];
    int inicio;
    int fim;
    int tamanho;
} FilaMedico;

// N� para Fila Din�mica da Enfermagem
typedef struct NoEnfermagem {
    Paciente paciente;
    struct NoEnfermagem *proximo;
} NoEnfermagem;

// Fila Din�mica para Enfermagem (sem limite)
typedef struct {
    NoEnfermagem *inicio;
    NoEnfermagem *fim;
    int tamanho;
} FilaEnfermagem;

// Fun��es para Fila do M�dico (Est�tica)
FilaMedico* criarFilaMedico();
int agendarMedico(FilaMedico *fila, char *nome, char *data, char *hora);
int atenderMedico(FilaMedico *fila);
void listarAgendamentosMedico(FilaMedico *fila);
int filaCheiaMedico(FilaMedico *fila);
int filaVaziaMedico(FilaMedico *fila);
void liberarFilaMedico(FilaMedico *fila);

// Fun��es para Fila da Enfermagem (Din�mica)
FilaEnfermagem* criarFilaEnfermagem();
int agendarEnfermagem(FilaEnfermagem *fila, char *nome, char *data, char *hora);
int atenderEnfermagem(FilaEnfermagem *fila);
void listarAgendamentosEnfermagem(FilaEnfermagem *fila);
int filaVaziaEnfermagem(FilaEnfermagem *fila);
void liberarFilaEnfermagem(FilaEnfermagem *fila);

// Fun��es utilit�rias
void mostrarStatusFilas(FilaMedico *filaMedico, FilaEnfermagem *filaEnfermagem);

#endif

