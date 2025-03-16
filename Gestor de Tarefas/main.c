#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor_tarefas.h"

int main() {
    Task* task_list[MAX_PRIORITY + 1] = {NULL};

    char command[100];
    while (1) {
        printf("> ");
        if (!fgets(command, sizeof(command), stdin)) break;

        if (strncmp(command, "new", 3) == 0) {
            int priority;
            char id[50];
            if (sscanf(command + 4, "%d %49s", &priority, id) == 2) {
                if (priority < 1 || priority > MAX_PRIORITY) {
                    printf("Prioridade inválida. Deve estar entre 1 e %d.\n", MAX_PRIORITY);
                    continue;
                }
                Task* new_task = create_task(priority, id);
                if (!new_task) {
                    printf("Erro ao criar a tarefa.\n");
                    continue;
                }
                if (add_task(&task_list[priority], new_task) == 0) {
                    printf("Tarefa '%s' adicionada com sucesso.\n", id);
                } else {
                    printf("Erro ao adicionar a tarefa '%s'.\n", id);
                    free(new_task);
                }
            } else {
                printf("Comando inválido. Use: new <prioridade> <id>\n");
            }
        } else if (strncmp(command, "list", 4) == 0) {
            int min_priority;
            if (sscanf(command + 5, "%d", &min_priority) == 1) {
                if (min_priority < 1 || min_priority > MAX_PRIORITY) {
                    printf("Prioridade mínima inválida. Deve estar entre 1 e %d.\n", MAX_PRIORITY);
                    continue;
                }
                for (int i = MAX_PRIORITY; i >= min_priority; i--) {
                    list_tasks(task_list[i], min_priority);
                }
            } else {
                printf("Comando inválido. Use: list <prioridade mínima>\n");
            }
        } else if (strncmp(command, "complete", 8) == 0) {
            char id[50];
            if (sscanf(command + 9, "%49s", id) == 1) {
                int found = 0;
                for (int i = MAX_PRIORITY; i >= 1; i--) {
                    if (complete_task(&task_list[i], id) == 0) {
                        printf("Tarefa '%s' concluída com sucesso.\n", id);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("TAREFA INEXISTENTE\n");
                }
            } else {
                printf("Comando inválido. Use: complete <id>\n");
            }
        } else if (strncmp(command, "exit", 4) == 0) {
            break;
        } else {
            printf("Comando desconhecido.\n");
        }
    }

    // Liberar memória alocada
    for (int i = 1; i <= MAX_PRIORITY; i++) {
        Task* current = task_list[i];
        while (current) {
            Task* temp = current;
            current = current->next;
            free(temp);
        }
    }


}
 
