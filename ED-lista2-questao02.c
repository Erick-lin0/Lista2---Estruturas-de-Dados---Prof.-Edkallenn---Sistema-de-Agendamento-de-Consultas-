/*
** Fun��o : Sistema de Agendamento de Consultas M�dicas
** Autor : Erick e Daysila
** Data : 18/06/2025
** Observa��es: Sistema para cl�nica m�dica com filas EST�TICA para m�dico e  DIN�MICA para enfermagem
*/

#include "agendamento.h"
#include <stdio.h>
#include <string.h>

int main() {
    FilaMedico *filaMedico = criarFilaMedico();
    FilaEnfermagem *filaEnfermagem = criarFilaEnfermagem();
    
    int opcao;
    char nome[MAX_NOME];
    char data[MAX_DATA];
    char hora[MAX_HORA];
    
    printf("=== SISTEMA DE AGENDAMENTO ===\n\n");
    
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Agendar consulta com M�dico\n");
        printf("2. Agendar consulta com Enfermagem\n");
        printf("3. Atender pr�ximo paciente do M�dico\n");
        printf("4. Atender pr�ximo paciente da Enfermagem\n");
        printf("5. Listar agendamentos do M�dico\n");
        printf("6. Listar agendamentos da Enfermagem\n");
        printf("7. Status das filas\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer
        
        switch(opcao) {
            case 1:
                printf("\n--- AGENDAMENTO COM M�DICO ---\n");
                printf("Nome do paciente: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                printf("Data (DD/MM/AAAA): ");
                fgets(data, MAX_DATA, stdin);
                data[strcspn(data, "\n")] = 0;
                
                printf("Hora (HH:MM): ");
                fgets(hora, MAX_HORA, stdin);
                hora[strcspn(hora, "\n")] = 0;
                
                agendarMedico(filaMedico, nome, data, hora);
                break;
                
            case 2:
                printf("\n--- AGENDAMENTO COM ENFERMAGEM ---\n");
                printf("Nome do paciente: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                printf("Data (DD/MM/AAAA): ");
                fgets(data, MAX_DATA, stdin);
                data[strcspn(data, "\n")] = 0;
                
                printf("Hora (HH:MM): ");
                fgets(hora, MAX_HORA, stdin);
                hora[strcspn(hora, "\n")] = 0;
                
                agendarEnfermagem(filaEnfermagem, nome, data, hora);
                break;
                
            case 3:
                atenderMedico(filaMedico);
                break;
                
            case 4:
                atenderEnfermagem(filaEnfermagem);
                break;
                
            case 5:
                listarAgendamentosMedico(filaMedico);
                break;
                
            case 6:
                listarAgendamentosEnfermagem(filaEnfermagem);
                break;
                
            case 7:
                mostrarStatusFilas(filaMedico, filaEnfermagem);
                break;
                
            case 0:
                printf("Encerrando sistema...\n");
                break;
                
            default:
                printf("Op��o inv�lida!\n");
                break;
        }
    } while(opcao != 0);
    
    liberarFilaMedico(filaMedico);
    liberarFilaEnfermagem(filaEnfermagem);
    
    return 0;
}

