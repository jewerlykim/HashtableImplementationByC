// 링크드 리스트를 이용한 해시테이블 구현 (충돌 - 체이닝)
#include <stdio.h>
#include <stdlib.h>

struct bucket* hashTable = NULL;
int SIZE = 10;

// 노드 구조체
struct node{
    int key;
    int value;
    struct node* next;
};
// 버켓
struct bucket{
    struct node* head;
    int count; // 버켓에 몇개가 들어가는지
};

struct node* createNode(int key, int value){
    struct node* newNode;
    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

int hashFunction(int key){
    return key%SIZE;
}

void insert(int key, int value){
    int hashIndex = hashFunction(key);

    struct node* newNode = createNode(key, value);
    // 아무 노드가 없는 경우
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode;
    }
    // 내가 넣고자 하는 인덱스에 이미 값이 있는 경우
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
    return;
}

void remove_key(int key){
    int hashIndex = hashFunction(key);
    
    struct node* node;
    struct node* trace;

    node = hashTable[hashIndex].head;

    if (node == NULL){
        printf("\n no key found");
        return;
    }
    while (node != NULL)
    {
        if(node->key == key){
            // 포인터 바꾸어 주는 부분
            if(node == hashTable[hashIndex].head){
                hashTable[hashIndex].head = node->next;
            }
            else{
                trace->next = node->next;
            }
            hashTable[hashIndex].count--;
            free(node);
            return;
        }
        trace = node;
        node = node->next;
    }
    printf("\n no key found");
    return;   
}

void search(int key){
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;

    if(node == NULL){
        printf("\n no key found");
        return;
    }
    while (node != NULL)
    {
        if (node->key == key){
            printf("\nkey found key = [%d], value = [%d] ", node->key, node->value);
            return;
        }

        node = node->next;
    }
    printf("\nno key found");
    return;
}

void display(){
    struct node* horse;

    printf("\n========= display start ========= \n");
    for (int i = 0; i<SIZE; i++){
        horse = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (horse != NULL)
        {
            printf("(key : %d, val : %d)  -> ", horse->key, horse->value);
            horse = horse->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
    return;
}

int main(){

    hashTable = (struct bucket *)malloc(SIZE * sizeof(struct bucket));

    insert(0, 1);
    insert(1, 10);
    insert(11, 12);
    insert(21, 14);
    insert(31, 16);
    insert(5, 18);
    insert(7, 19);

    display();

    remove_key(31);
    remove_key(11);

    display();

    search(11);
    search(1);

}