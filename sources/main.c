#include <assert.h>
#include <stdlib.h>

#include "hash.h"

void test_new(){
    int size = 10;
    HashTable h = hashtable_new(size);
    HashTable* ht = &h;
    assert(ht != NULL && ht->tableSize == size);
}

void test_add(){
    HashTable* ht = hashtable_new_ptr(10);
    hashtable_addElement(ht, "Sudheer");
    hashtable_addElement(ht, "Karthik");
    hashtable_addElement(ht, "Sudheer");
    assert(ht != NULL && hashtable_lookup(ht, "Sudheer"));
}

void test_del(){
    HashTable* ht = hashtable_new_ptr(10);
    hashtable_addElement(ht, "Sudheer");
    hashtable_addElement(ht, "Karthik");
    hashtable_delElement(ht, "Sudheer");
    assert(ht != NULL && !hashtable_lookup(ht, "Sudheer"));
}

int main(){
    test_new();
    test_add();
    test_del();
    return 0;
}