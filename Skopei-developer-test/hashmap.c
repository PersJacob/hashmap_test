#include "hashmap.h"

int hash(HashMap * hm, char * key) {
	int sum = 0;
	int len = strlen(key) + 1;

	for (int i = 0; i < len; i++) {
		sum = sum + key[i];
	}

	return sum % hm->size;
}

HashMap * create_hashmap(size_t key_size) {
	assert(key_size > 0);

	HashMap * hm = (HashMap *) malloc(sizeof(HashMap));
	assert(hm);

	hm->buckets = calloc(key_size, sizeof(Bucket));
	assert(hm->buckets);

	hm->size  = key_size; 

	return hm;
}

void insert_data(HashMap * hm, char * key, void * data, ResolveCollisionCallback resolve_collision) {
}

void * get_data(HashMap * hm, char * key) {
}

void iterate(HashMap * hm, void (* callback)(char * key, void * data)) {
}

void remove_data(HashMap * hm, char * key, DestroyDataCallback destroy_data) {
}

void delete_hashmap(HashMap * hm, DestroyDataCallback destroy_data) {
}
