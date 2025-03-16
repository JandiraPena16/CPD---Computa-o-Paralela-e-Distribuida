#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor_tarefas.h"

// Função para criar uma nova tarefa
Task* create_task(int priority, const char* id) {
    Task* new_task = (Task*)malloc(sizeof(Task));
    if (!new_task) {
        perror("Erro ao alocar memória");
        return NULL;
    }
    new_task->priority = priority;
    strncpy(new_task->id, id, sizeof(new_task->id) - 1);
    new_task->id[sizeof(new_task->id) - 1] = '\0';
    new_task->next = NULL;
    return new_task;
}

// Função para adicionar uma tarefa à lista de tarefas
int add_task(Task** head, Task* new_task) {
    if (!head || !new_task) return -1;

    if (!*head || (*head)->priority < new_task->priority) {
        new_task->next = *head;
        *head = new_task;
    } else {
        Task* current = *head;
        while (current->next && current->next->priority >= new_task->priority) {
            current = current->next;
        }
        new_task->next = current->next;
        current->next = new_task;
    }
    return 0;
}

// Função para listar as tarefas com prioridade mínima
void list_tasks(Task* head, int min_priority) {
    Task* current = head;
    while (current) {
        if (current->priority >= min_priority) {
            printf("Prioridade: %d, ID: %s\n", current->priority, current->id);
        }
        current = current->next;
    }
}

// Função para completar (remover) uma tarefa da lista
int complete_task(Task** head, const char* id) {
    if (!head || !*head) return -1;

    Task* current = *head;
    Task* previous = NULL;

    while (current) {
        if (strcmp(current->id, id) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                *head = current->next;
            }
            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}
