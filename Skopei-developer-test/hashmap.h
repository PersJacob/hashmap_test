#define __HASHMAP_H__
#define MAX_KEY_SIZE = 128;

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Bucket {
	struct Bucket * next;
	char * key;
	void * data;
} Bucket;

typedef struct HashMap {
	Bucket ** buckets;
	size_t size;
} HashMap;  

typedef void * (* ResolveCollisionCallback)(void * old_data, void * new_data);

typedef void (* DestroyDataCallback)(void * data);

extern int hash();
extern HashMap * create_hashmap();
extern void insert_data();
extern void * get_data();
extern void iterate();
extern void remove_data();
extern void delete_hashmap();
extern char *strdup_replacement(const char *str);