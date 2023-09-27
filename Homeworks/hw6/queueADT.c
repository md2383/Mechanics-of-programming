// File: $Id: queueADT.c,v 1.0 2023/07/18 10:33:00 csci243 Exp $
//
// Description:  Queue ADT module
//
// Author:  Miguel Dias Pinto (md2383)
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define QUEUE_SIZE 64

struct QueueNode {
    void *data;
    struct QueueNode *next;
};

struct queueStruct {
    struct QueueNode *front;
    struct QueueNode *rear;
    int (*cmp)(const void *, const void *);
};

typedef struct queueStruct *QueueADT;

#define _QUEUE_IMPL_
#include "queueADT.h"

QueueADT que_create(int (*cmp)(const void *a, const void *b)) {
    QueueADT queue = (QueueADT)malloc(sizeof(struct queueStruct));
    if (queue != NULL) {
        queue->front = NULL;
        queue->rear = NULL;
        queue->cmp = cmp;
    }
    return queue;
}

void que_destroy(QueueADT queue) {
    if (queue != NULL) {
        que_clear(queue);
        free(queue);
    }
}

void que_clear(QueueADT queue) {
    if (queue != NULL) {
        while (!que_empty(queue)) {
            que_remove(queue);
        }
    }
}

void que_insert(QueueADT queue, void *data) {
    if (queue != NULL) {
        struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
        if (newNode != NULL) {
            newNode->data = data;
            newNode->next = NULL;

            if (queue->cmp == NULL) {
                if (queue->front == NULL) {
                    queue->front = newNode;
                    queue->rear = newNode;
                } else {
                    queue->rear->next = newNode;
                    queue->rear = newNode;
                }
            } else {
                struct QueueNode *curr = queue->front;
                struct QueueNode *prev = NULL;

                while (curr != NULL && queue->cmp(data, curr->data) >= 0) {
                    prev = curr;
                    curr = curr->next;
                }

                if (prev == NULL) {
                    newNode->next = queue->front;
                    queue->front = newNode;
                } else {
                    prev->next = newNode;
                    newNode->next = curr;
                    if (curr == NULL) {
                        queue->rear = newNode;
                    }
                }
            }
        }
    }
}


void *que_remove(QueueADT queue) {
    if (queue != NULL && queue->front != NULL) {
        struct QueueNode *temp = queue->front;
        void *data = temp->data;

        queue->front = queue->front->next;
        free(temp);

        if (queue->front == NULL) {
            queue->rear = NULL;
        }

        return data;
    }

    printf("ERROR: Invalid queue or queue is empty\n");
    return NULL;
}


bool que_empty(QueueADT queue) {
    return queue == NULL || queue->front == NULL;
}