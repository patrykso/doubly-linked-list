#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

struct Element {
    unsigned long long int key;
    struct Element* next;
    struct Element* prev;
};

void quit(struct Element** head) { //freeing memory
    if (*head == nullptr) return;
    struct Element* tmp = nullptr;
    while (*head != nullptr) {
        tmp = (*head)->next;
        delete *head;
        *head = tmp;
    }
}

void print(char position[], struct Element* head, struct Element* iterators[]) {
    if (!strcmp(position, "ALL")) {
        struct Element* tmp = head;
        while (tmp != nullptr) {
            cout << tmp->key << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    else {
        int pos = atoi(position);
        if (iterators[pos] != nullptr) cout << iterators[pos]->key << endl;
    }
}

void initializeIterator(unsigned long long int tmpKey, char position[], struct Element** head, struct Element** tail, struct Element* iterators[]) {
    if (!strcmp(position, "BEG")) iterators[tmpKey] = *head;
    else if (!strcmp(position, "END")) iterators[tmpKey] = *tail;
    else {
        int pos = atoi(position);
        if (iterators[pos] != nullptr) iterators[tmpKey] = iterators[pos];
    }
}

void addBefore(struct Element** head, struct Element** tail, unsigned long long int tmpKey, char position[], struct Element* iterators[]) {
    struct Element* newElement = new Element;
    newElement->key = tmpKey;
    int pos = atoi(position);
    if (*head == nullptr) {
        *head = newElement;
        *tail = newElement;
        newElement->next = nullptr;
        newElement->prev = nullptr;
    }
    else if (!strcmp(position, "END") || iterators[pos] == *tail) {
        newElement->next = *tail;
        newElement->prev = (*tail)->prev;
        if ((*tail)->prev != nullptr) (*tail)->prev->next = newElement;
        (*tail)->prev = newElement;
    }
    else if (!strcmp(position, "BEG") || iterators[pos] == *head) {
        newElement->prev = nullptr;
        newElement->next = *head;
        (*head)->prev = newElement;
        if ((*head)->next == nullptr) *tail = *head;
        *head = newElement;
    }
    else {
        if (iterators[pos] != nullptr) {
            newElement->next = iterators[pos];
            newElement->prev = iterators[pos]->prev;
            if (iterators[pos]->prev != nullptr) iterators[pos]->prev->next = newElement;
            iterators[pos]->prev = newElement;
        }
    }
}

void addAfter(struct Element** head, struct Element** tail, unsigned long long int tmpKey, char position[], struct Element* iterators[]) {
    struct Element* newElement = new Element;
    newElement->key = tmpKey;
    int pos = atoi(position);
    if (*head == nullptr) {
        *head = newElement;
        *tail = newElement;
        newElement->next = nullptr;
        newElement->prev = nullptr;
    }
    else if (!strcmp(position, "END") || iterators[pos] == *tail) {
        newElement->next = nullptr;
        newElement->prev = (*tail);
        (*tail)->next = newElement;
        *tail = newElement;
    }
    else if (!strcmp(position, "BEG") || iterators[pos] == *head) {
        newElement->prev = *head;
        newElement->next = (*head)->next; //
        if ((*head)->next != nullptr) (*head)->next->prev = newElement;
        (*head)->next = newElement;
        if (newElement->next == nullptr) *tail = newElement;
    }
    else {
        if (iterators[pos] != nullptr) {
            newElement->prev = iterators[pos];
            newElement->next = iterators[pos]->next;
            if (iterators[pos]->next != nullptr) iterators[pos]->next->prev = newElement;
            iterators[pos]->next = newElement;
        }
    }
}

void moveIteratorForward(struct Element* iterators[], unsigned long long int tmpKey) {
    if (iterators[tmpKey]->next != nullptr) iterators[tmpKey] = iterators[tmpKey]->next;
}

void moveIteratorBackward(struct Element* iterators[], unsigned long long int tmpKey) {
    if (iterators[tmpKey]->prev != nullptr) iterators[tmpKey] = iterators[tmpKey]->prev;
}

bool checkIfIteratorsPointsToRemovedElement (int i, struct Element** removedElement, struct Element* iterators[]) {
    if (iterators[i] == *removedElement) return true;
    return false;
}

void remove(char position[], struct Element** head, struct Element** tail, struct Element* iterators[]) {
    int pos = atoi(position);
    if (*head == nullptr && *tail == nullptr) return; //empty list
    else if (!strcmp(position, "BEG") || iterators[pos] == *head) { //deleting head
        struct Element* tmp = *head;
        if ((*head)->next != nullptr) {
            for (int i = 0; i < 10; i++) {
                if (checkIfIteratorsPointsToRemovedElement(i, head, iterators)) moveIteratorForward(iterators, i); //if next element exists, move iterators
            }
            *head = (*head)->next;
            if ((*head)->prev != nullptr) (*head)->prev = nullptr;
            delete tmp;
        }
        else {
            *head = nullptr;
            *tail = nullptr;
            for (int i = 0; i < 10; i++) iterators[i] = nullptr;
            delete tmp;
        }
    }
    else if (!strcmp(position, "END") || iterators[pos] == *tail) { //deleting tail
        struct Element* tmp = *tail;
        if ((*tail)->prev != nullptr) {
            for (int i = 0; i < 10; i++) {
                if (checkIfIteratorsPointsToRemovedElement(i, tail, iterators)) moveIteratorBackward(iterators, i); //if prev element exists, move iterators
            }
            *tail = (*tail)->prev;
            if ((*tail)->next != nullptr) (*tail)->next = nullptr;
            delete tmp;
        }
        else {
            *head = nullptr;
            *tail = nullptr;
            for (int i = 0; i < 10; i++) iterators[i] = nullptr;
            delete tmp;
        }
    }
    else { //removing element using iterators
        struct Element* removedElement = iterators[pos];
        if (iterators[pos]->next != nullptr) (iterators[pos])->next->prev = (iterators[pos])->prev;
        if (iterators[pos]->prev != nullptr) (iterators[pos])->prev->next = (iterators[pos])->next;
        for (int i = 0; i < 10; i++) {
            if (checkIfIteratorsPointsToRemovedElement(i, &removedElement, iterators)) moveIteratorForward(iterators, i); //if next element exists, move iterators
        }
        delete removedElement;
    }
}

int main() {
    char command[100], position[40];
    unsigned long long int tmpKey = 0;
    struct Element* head = nullptr;
    struct Element* tail = nullptr;
    struct Element* iterators[10];
    for (int i = 0; i < 10; i++) iterators[i] = nullptr;
    while (scanf("%s", command)) {
        if (feof(stdin) != 0) break;
        else if (!strcmp(command, "i")) {
            cin >> tmpKey >> position;
            initializeIterator(tmpKey, position, &head, &tail, iterators);
        }
        else if (!strcmp(command, "+")) {
            cin >> tmpKey;
            moveIteratorForward(iterators, tmpKey);
        }
        else if (!strcmp(command, "-")) {
            cin >> tmpKey;
            moveIteratorBackward(iterators, tmpKey);
        }
        else if (!strcmp(command, ".A")) {
            cin >> position >> tmpKey;
            addBefore(&head, &tail, tmpKey, position, iterators);
        }
        else if (!strcmp(command, "A.")) {
            cin >> position >> tmpKey;
            addAfter(&head, &tail, tmpKey, position, iterators);
        }
        else if (!strcmp(command, "R")) {
            cin >> position;
            remove(position, &head, &tail, iterators);
        }
        else if (!strcmp(command, "P")) {
            cin >> position;
            print(position, head, iterators);
        }
        else if (!strcmp(command, "Q")) break;
    }
    quit(&head);
    return 0;
}