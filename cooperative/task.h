#ifndef TASK_H
#define TASK_H

typedef enum state {
    RUNNING, READY, BLOCKED, FAULTED
}state;

typedef struct{
    int id;
    int priority;
    state state;
    void (*code)(void);
} Task;

#endif
