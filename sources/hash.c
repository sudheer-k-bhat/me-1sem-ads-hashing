#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hash.h"

HashTable hashtable_new(uint32_t size)
{
    //TODO use next nearest prime number if size if not prime
    HashTable ht = {size, (Node **)malloc(sizeof(Node *) * size)};
    for (uint32_t i = 0; i < ht.tableSize; i++)
    {
        ht.tableAddress[i] = NULL;
    }
    return ht;
}

HashTable* hashtable_new_ptr(uint32_t size){
    HashTable* ht = (HashTable*) malloc(sizeof(HashTable*));
    ht->tableSize = size;
    ht->tableAddress = (Node **)malloc(sizeof(Node *) * size);
    for (uint32_t i = 0; i < ht->tableSize; i++)
    {
        ht->tableAddress[i] = NULL;
    }
    return ht;
}
//using cyclic shift code
static int32_t _hash_(char *data)
{
    int32_t hashcode = 0;
    while (*data != '\0')
    {
        hashcode = (hashcode << 5) + *data++;
    }
    return hashcode;
}

static uint32_t _compression_(int32_t hashcode, uint32_t tableSize)
{
    return (hashcode % tableSize);
}

static uint32_t _hashing_(char *data, uint32_t tableSize)
{
    int32_t hashcode = _hash_(data);
    uint32_t index = _compression_(hashcode, tableSize);
    return index;
}

uint32_t hashtable_lookup(HashTable *ht, char *data)
{
    assert(ht != NULL);
    Node *nodeAdd = ht->tableAddress[_hashing_(data, ht->tableSize)];
    while (nodeAdd != NULL)
    {
        if (!strcmp(nodeAdd->name, data))
        {
            break;
        }
        else
        {
            nodeAdd = nodeAdd->next;
        }
    }
    return (nodeAdd != NULL);
}

HashTable *hashtable_addElement(HashTable *ht, char *data)
{
    assert(ht != NULL);
    if (!hashtable_lookup(ht, data))
    {
        uint32_t bucket = _hashing_(data, ht->tableSize);
        Node *oldAdd = ht->tableAddress[bucket];
        ht->tableAddress[bucket] = (Node *)malloc(sizeof(Node));
        strcpy(ht->tableAddress[bucket]->name, data);
        ht->tableAddress[bucket]->next = oldAdd;
    }
    return ht;
}

HashTable *hashtable_delElement(HashTable *ht, char *data)
{
    assert(ht != NULL);
    uint32_t bucket = _hashing_(data, ht->tableSize);
    Node *node = ht->tableAddress[bucket];
    if (node != NULL)
    {
        if (strcmp(node->name, data) == 0)
        {
            ht->tableAddress[bucket] = node->next;
            node->next = NULL;
            free(node);
        }
        else
        {
            Node *prev = node;
            node = node->next;
            while (node != NULL)
            {
                if (strcmp(node->name, data) == 0)
                {
                    prev->next = node->next;
                    node->next = NULL;
                    free(node);
                }
                prev = node;
                node = node->next;
            }
        }
    }
    return ht;
}