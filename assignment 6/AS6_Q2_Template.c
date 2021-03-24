#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
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
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
   //Write your code here
   //whether key is negative
    int key_inverse = key;
    while (key_inverse < 0)
        key_inverse += TABLESIZE;
    //cnt is the variable to count the number of comparation and two indexes are used to present two hash functions
    int cnt = 0, num;
    int index_1, index_2;
    int dele;
    index_1 = hash1(key_inverse);
    index_2 = hash2(key_inverse);
    //find out the slopt which has not been used
    while (hashTable[index_1].indicator == USED && cnt < TABLESIZE) {
        //check whether the key has already inside the hash table
        if (hashTable[index_1].key == key)
            return -1;
        index_1 = (index_1 + index_2)%TABLESIZE;
        ++cnt;
    }
    //check the rest hash table
    num = cnt;
    int ins = index_1;
    do {
        ++num;
        index_1 = (index_1 + index_2)%TABLESIZE;
        if (hashTable[index_1].key == key && hashTable[index_1].indicator == USED)
            return -1;
        if (hashTable[index_1].key == key && hashTable[index_1].indicator == DELETED) {
            hashTable[index_1].indicator = USED;
            return num;
        }
    } while (hashTable[index_1].indicator != EMPTY && num <= TABLESIZE);

    //if the slot is previously empty or deleted
    if (cnt != TABLESIZE) {
        hashTable[ins].key = key;
        hashTable[ins].indicator = USED;
    }
    
    return cnt;
}

int HashDelete(int key, HashSlot hashTable[])
{
    //Write your code here
    //whether key is negative
    int key_inverse = key;
    while (key_inverse < 0)
        key_inverse += TABLESIZE;
    //cnt is the variable to count the number of comparation and two indexes are used to present two hash functions
    int cnt = 0;
    int found = 0;
    int index_1, index_2;
    index_1 = hash1(key_inverse);
    index_2 = hash2(key_inverse);
    //find out the key
    while (hashTable[index_1].indicator != EMPTY && cnt < TABLESIZE) {
        ++cnt;

        if (hashTable[index_1].key == key)
            //delete the node
            if (hashTable[index_1].indicator == USED) {
                hashTable[index_1].indicator = DELETED;
                found = 1;
                break;
            }
            //if the key has already been deleted
            else if (hashTable[index_1].indicator == DELETED)
                return -1;
        index_1 = (index_1 + index_2)%TABLESIZE;
    }
    
    if (!found)
        return -1;
    
    return cnt;
}
