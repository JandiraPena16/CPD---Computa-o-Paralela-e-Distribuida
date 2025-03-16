#ifndef GESTOR_TAREFAS_H
#define GESTOR_TAREFAS_H

#define MAX_PRIORITY 5

// Estrutura para representar uma tarefa
typedef struct Task {
    int priority;
    char id[50];
    struct Task* next;
} Task;

// Funções para manipulação das tarefas
Task* create_task(int priority, const char* id);
int add_task(Task** head, Task* new_task);
void list_tasks(Task* head, int min_priority);
int complete_task(Task** head, const char* id);

#endif // GESTOR_TAREFAS_H
