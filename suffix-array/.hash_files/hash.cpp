// hash.cpp

#include "hash.h"
#include <iostream>

using namespace std;

hash_table* init_table(unsigned int cap) {
    hash_table* table = new hash_table;
    table->capacity = cap;
    table->size = 0;
    table->occupied = 0;
    table->table = new hash_node*[cap];

    // initialize all hash_nodes to null
    for (unsigned int i=0; i < cap; i++) {
        table->table[i] = nullptr;
    }

    table->hash_func = djb2;
    table->bucket_func = modulo_bucket_func;
    return table;
}

hash_node* init_node(std::string key, unsigned int hashcode, std::string val) {
    hash_node* node = new hash_node;
    node->deleted = 0;
    node->key = key;
    node->hashcode = hashcode;
    node->value = val;
    return node;
}

bool set_kvp(hash_table* tbl, string key, string value) {

    // If table is already at capacity with filled buckets
    if (tbl->size >= tbl->capacity) {
        return false;
    }

    unsigned int hash = tbl->hash_func(key);
    unsigned int bucket_index = tbl->bucket_func(hash, tbl->capacity);
    hash_node* bucket = tbl->table[bucket_index];
    hash_node* node = init_node(key, hash, value);

    //
    if (bucket == nullptr) {
        // No node assigned to bucket
        tbl->table[bucket_index]= node;

        // Increment attributes
        tbl->size++;
        tbl->occupied++;

    } else if (bucket->hashcode != hash) {
        int i = bucket_index;
        while ( bucket ) {
            i = (i + 1) % tbl->capacity;
            bucket = tbl->table[i];
        }

        tbl->table[bucket_index] = node;

        // Increment attributes
        tbl->size++;
        tbl->occupied++;
    } else {
        // update the value at the bucket
        tbl->table[bucket_index]->value = value;
    }

    return true;
}

float load(hash_table* tbl) {
    return (float)tbl->size / (float)tbl->capacity;
}

string get_val(hash_table* tbl, std::string key) {
    unsigned int hashcode = tbl->hash_func(key);
    int bucket_idx = tbl->bucket_func(hashcode, tbl->capacity);
    hash_node* bucket = tbl->table[bucket_idx];

    // ONly get the value of a non-deleted bucket
    if ( bucket && (!bucket->deleted) ) {
        return bucket->value;
    }

    return "";
}

bool contains(hash_table* tbl, std::string key) {
    unsigned int hashcode = tbl->hash_func(key);
    int bucket_idx = tbl->bucket_func(hashcode, tbl->capacity);
    hash_node* bucket = tbl->table[bucket_idx];

    // ONly get the value of a non-deleted bucket
    if ( bucket && (!bucket->deleted) ) {
        return true;
    }

    return false;
}

bool remove(hash_table* tbl, std::string key) {
    if (!contains(tbl, key)) {
        return false;
    }

    unsigned int hashcode = tbl->hash_func(key);
    int bucket_idx = tbl->bucket_func(hashcode, tbl->capacity);
    hash_node* bucket = tbl->table[bucket_idx];

    bucket->deleted = true;

    tbl->size--;

    return 1;
}

void resize(hash_table* tbl, unsigned int new_capacity) {
}

// implemented for you - feel free to change this one
void print_table(hash_table* tbl) {
    cout << "Hashtable:" << endl;
    cout << "  capacity: " << tbl->capacity << endl;
    cout << "  size:     " << tbl->size << endl;
    cout << "  occupied: " << tbl->occupied << endl;
    cout << "  load:     " << load(tbl) << endl;
    if (tbl->capacity < 130) {
        for (unsigned int i=0; i < tbl->capacity; i++) {
            cout << "[" << i << "]    ";
            if (tbl->table[i] == NULL) {
                cout << "<empty>" << endl;
            } else if (tbl->table[i]->deleted) {
                cout << "<deleted>" << endl;
            } else {
                cout << "\"" << tbl->table[i]->key << "\" = \"" << tbl->table[i]->value << "\"" << endl;
            }
        }
    } else {
        cout << "    <hashtable too big to print out>" << endl;
    }
}

// implemented for you - don't change this one
unsigned int djb2(string key) {
    unsigned int hash = 5381;
    // Leaving the debugging stuff commented out, in case you want to
    // play. It will output the hash at each incremental step so you can
    // see how it takes shape.
    //
    //  cout << "Hashing string \"" << key << "\"" << endl;
    //  cout << bitset<32>(hash) << " " << hash << endl;
    for (size_t i=0; i < key.length(); i++) {
        char c = key[i];
        hash = ((hash << 5) + hash) + c;
        // cout << bitset<32>(hash) << " " << hash << endl;
    }
    // cout << "Hashed string \"" << key << "\" to " << hash << endl;
    //
    // for light reading on why djb2 might not be the best
    // production-grade hash function, go to
    // http://dmytry.blogspot.com/2009/mod11/horrible-hashes.html
    return hash;
}

// implemented for you - don't change this one
unsigned int modulo_bucket_func(unsigned int hashcode, unsigned int cap) {
    unsigned int b = hashcode % cap;
    return b;
}
