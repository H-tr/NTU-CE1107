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
    //cnt is the variable to count the number of comparation and two indexes are used to present two hash functions
    int cnt = 0, num = TABLESIZE;
    int index_1, index_2;
    int dele = -1;
    index_1 = hash1(key);
    index_2 = hash2(key);
    //find out the slopt which has not been used
    while (hashTable[index_1].indicator != EMPTY && cnt < num) {
        if (hashTable[index_1].indicator == USED) {
            if (hashTable[index_1].key == key)
                return -1;
            ++cnt;
        }
        else {
            if (dele == -1)
                dele = index_1;
            --num;
        } 
        index_1 = hash1(index_1 + index_2);
    }
    
    if (dele == -1) {
        if (cnt == TABLESIZE)
            return cnt;
        hashTable[index_1].indicator = USED;
        hashTable[index_1].key = key;
    }
    else {
        hashTable[dele].indicator = USED;
        hashTable[dele].key = key;
    }
    return cnt;
}

int HashDelete(int key, HashSlot hashTable[])
{
    //Write your code here
    //cnt is the variable to count the number of comparation and two indexes are used to present two hash functions
    int cnt = 0, num = TABLESIZE;
    int index_1, index_2;
    index_1 = hash1(key);
    index_2 = hash2(key);
    //if we don't count the deleted in number of comparation
    /*while (hashTable[index_1].indicator != EMPTY && cnt < num) {
        if (hashTable[index_1].indicator == USED) {
            ++cnt;
            if (hashTable[index_1].key == key) {
                hashTable[index_1].indicator = DELETED;
                return cnt;
            }
        }
        else
            --num;
        index_1 = hash1(index_1 + index_2);
    }*/

    //if we consider the deleted in number of comparation
    while (hashTable[index_1].indicator != EMPTY && cnt < TABLESIZE) {
        ++cnt;
        if (hashTable[index_1].indicator == USED && hashTable[index_1].key == key) {
            hashTable[index_1].indicator = DELETED;
            return cnt;
        }
        index_1 = hash1(index_1 + index_2);
    }
    //the two cases above do not affect the result.

    return -1;
}
