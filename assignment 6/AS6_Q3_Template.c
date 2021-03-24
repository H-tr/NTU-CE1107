#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
    // Write your code here
    //index_1 and index_2 are variables to represent the base index and addition index
    int key_inverse = key;
    if (key_inverse < 0)
        key_inverse = -key_inverse;

    int index_1 = hash(key_inverse);
    //declare a vriable to store the last slot with "next" and a variable to count
    int last = index_1;
    int cnt = 0;
    //find out the place to insert
    while (hashTable[index_1].indicator != EMPTY && cnt < TABLESIZE) {
        if (hashTable[index_1].key == key)
            return -1;
        
        if (hashTable[index_1].next != -1)
            index_1 = hashTable[index_1].next;
        else 
            index_1 = (index_1 + 1)%TABLESIZE;
                    
        cnt++;
    }
    //motify the "next" of last slot
    while (hashTable[last].next != -1)
        last = hashTable[last].next;
    
    if (last != index_1)
        hashTable[last].next = index_1;
    //insert the key
    hashTable[index_1].key = key;
    hashTable[index_1].indicator = USED;
    if (cnt == TABLESIZE)
        return cnt;
    return index_1;
}

int HashFind(int key, HashSlot hashTable[])
{
    // Write your code here
    //find out the base index of this key
    int key_inverse = key;
    if (key_inverse < 0)
        key_inverse = -key_inverse;
    int index = hash(key_inverse);
    while (1) {
        if (hashTable[index].key == key)
            return index;
        else if (hashTable[index].next == -1)
            return -1;
        else
            index = hashTable[index].next;
    }
}
