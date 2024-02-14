#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    char name[80];
    int priority;
    char time[15];
};

typedef struct Patient patient;

struct pqueue {
    patient* patients;
    int size;
};

typedef struct pqueue* pqueue;

pqueue create() {
    pqueue pq = (pqueue)malloc(sizeof(struct pqueue));
    pq->patients = (patient*)malloc(1000 * sizeof(patient));
    pq->size = 0;
    return pq;
}

void swap(patient* a, patient* b) {
    patient temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(pqueue pq, int index) {
    int curr = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < pq->size && pq->patients[left].priority > pq->patients[curr].priority)
        curr = left;
    if (right < pq->size && pq->patients[right].priority > pq->patients[curr].priority)
        curr = right;
    if (curr != index) {
        swap(&pq->patients[index], &pq->patients[curr]);
        heapify(pq, curr);
    }
}

void heapify_n(pqueue pq, int index, int n) {
    int curr = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < n && pq->patients[left].priority < pq->patients[curr].priority)
        curr = left;
    if (right < n && pq->patients[right].priority < pq->patients[curr].priority)
        curr = right;
    if (curr != index) {
        swap(&pq->patients[index], &pq->patients[curr]);
        heapify_n(pq, curr, n);
    }
}

void heapsort(pqueue pq) {
    int len = pq->size;
    for (int i = len / 2; i >= 0; i--) {
        heapify_n(pq, i, len);
    }
    for (int i = len - 1; i >= 0; i--) {
        swap(&pq->patients[0], &pq->patients[i]);
        heapify_n(pq, 0,i);
    }
}

void admitPatient(pqueue pq, char name[], int priority, char time[]) {
    patient newpatient;
    strcpy(newpatient.name, name);
    strcpy(newpatient.time, time);
    newpatient.priority = priority;
    int index = pq->size;
    pq->patients[index] = newpatient;
    pq->size++;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->patients[index].priority > pq->patients[index - 1].priority && (index - 1) != parent) {
            swap(&pq->patients[index], &pq->patients[index - 1]);
            index--;
        }
        if (pq->patients[index].priority > pq->patients[parent].priority) {
            swap(&pq->patients[index], &pq->patients[parent]);
            index = parent;
        }
        else
            break;
    }
}

void treat_next_patient(pqueue pq) {
    if (pq->size == 0) {
        printf("-1\n");
        return;
    }
    patient new = pq->patients[0];
    printf("%s %d %s\n", new.name, new.priority, new.time);
    pq->patients[0] = pq->patients[pq->size - 1];
    pq->size--;
    heapify(pq, 0);
}

void discharge_patient(pqueue pq, char name[], char time[]) {
    int index = -1;
    for (int i = 0; i < pq->size; i++) {
        if (strcmp(pq->patients[i].name, name) == 0 && strcmp(pq->patients[i].time, time) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("-1\n");
        return;
    }
    pq->patients[index] = pq->patients[pq->size - 1];
    pq->size--;
    heapify(pq, index);
}

void check_patient(pqueue pq) {
    if (pq->size == 0) {
        printf("-1\n");
        return;
    }
    patient new = pq->patients[0];
    printf("%s %d %s\n", new.name, new.priority, new.time);
}

void update_priority(pqueue pq, char name[], char time[], int newprior) {
    int index = -1;
    for (int i = 0; i < pq->size; i++) {
        if (strcmp(pq->patients[i].name, name) == 0 && strcmp(pq->patients[i].time, time) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("-1\n");
        return;
    }
    pq->patients[index].priority = newprior;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->patients[index].priority > pq->patients[parent].priority) {
            swap(&pq->patients[index], &pq->patients[parent]);
            index = parent;
        }
        else
            break;
    }
}

void print(pqueue pq) {
    if (pq->size == 0) {
        printf("-1\n");
        return;
    }
    heapsort(pq);
	for(int i=1;i<pq->size;i++){
		if(pq->patients[i-1].priority==pq->patients[i].priority){
			if(strcmp(pq->patients[i-1].time,pq->patients[i].time)>0){
				swap(&pq->patients[i],&pq->patients[i-1]);
			}
		}
	}
    for (int i = 0; i < pq->size; i++) {
        patient new = pq->patients[i];
        printf("%s %d %s\n", new.name, new.priority, new.time);
    }
}

int main() {
    pqueue pq = create();
    while (1) {
        char ch;
        scanf(" %c", &ch);  // Added space before %c to skip whitespace characters
        if (ch == 'e') {
            free(pq->patients);
            free(pq);
            return 0;
        }
        switch (ch) {
        case 'a':
            {
                char name[80];
                int priority;
                char admitTime[15];
                scanf("%s %d %s", name, &priority, admitTime);
                admitPatient(pq, name, priority, admitTime);
            }
            break;
        case 't':
            treat_next_patient(pq);
            break;
        case 'c':
            check_patient(pq);
            break;
        case 'd':
            {
                char name_discharge[80];
                char admitTime_discharge[15];
                scanf("%s %s", name_discharge, admitTime_discharge);
                discharge_patient(pq, name_discharge, admitTime_discharge);
            }
            break;
        case 'u':
            {
                char name_update[80];
                int newprior;
                char admitTime_update[15];
                scanf("%s %s %d", name_update, admitTime_update, &newprior);
                update_priority(pq, name_update, admitTime_update, newprior);
            }
            break;
        case 'p':
            print(pq);
            break;
        default:
            break;
        }
    }
}
