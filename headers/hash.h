#include <stdint.h>

#include "constants.h"

typedef struct _node_ Node;
struct _node_{
    char name[DATA_LEN];
    Node *next;
};

typedef struct {
    uint32_t tableSize;
    Node **tableAddress;
}HashTable;

HashTable hashtable_new(uint32_t size);
HashTable* hashtable_new_ptr(uint32_t size);
uint32_t hashtable_lookup(HashTable *ht, char *data);
HashTable* hashtable_addElement(HashTable *ht, char *data);
HashTable* hashtable_delElement(HashTable *ht, char *data);