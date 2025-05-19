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

/// @brief Inserts a key-data pair into the hash map. If the key already exists, resolves collision using the provided callback or overwrites the data
/// @param hm Pointer to the HashMap structure
/// @param key The key string to insert
/// @param data The data to associate with the key
/// @param resolve_collision Callback function to resolve data conflicts when the key already exists
void insert_data(HashMap * hm, char * key, void * data, ResolveCollisionCallback resolve_collision) {
	// Compute the bucket index
	size_t index = hash(hm, key); 

	// Point to the head of the linked list at the given bucket index in the hashmap.
	Bucket *current = hm->buckets[index];

	// Iterate over linked list to find if key already exists
	while (current) {
		// Compare string values of the keys
		if (strcmp(current->key, key) == 0) {
			// If key matches update data and return(if-statement to check if callback will be used)
			if (resolve_collision) {
				current->data = resolve_collision(current->data, data);
			} 
			else {
				current->data = data;
			}
			return;
		}
		current = current->next;
	}

	// If key not found, insert new bucket at the head of the list
	Bucket *new_bucket = malloc(sizeof(Bucket));
	// Copy key string
	new_bucket->key = strdup(key); 
	new_bucket->data = data;
	// Link to existing list
	new_bucket->next = hm->buckets[index]; 
	// Update head pointer
	hm->buckets[index] = new_bucket;
}

/// @brief Retrieves the data associated with a given key in the hash map
/// @param hm Pointer to the HashMap structure
/// @param key The key string to get
/// @return Pointer to the associated data or NULL if the key is not found
void * get_data(HashMap * hm, char * key) {
	
	if (!key) return NULL;
	
	size_t index = hash(hm, key); 
	Bucket *current = hm->buckets[index];

	// Iterate over linked list to find if key already exists
	while (current) {
		// If key matches, return data 
		if (strcmp(current->key, key) == 0) {
			return current->data; 
		}
		current = current->next;
	}

	return NULL; // If no key found, return NULL
}

/// @brief Iterates over all key-data pairs in the hash map and uses a callback function on each pair
/// @param hm Pointer to the HashMap structure
/// @param callback Function to be called with each key-data pair
void iterate(HashMap * hm, void (* callback)(char * key, void * data)) {
	// Iterate through the hashmap
	for (size_t i = 0; i < hm->size; i++) {
		Bucket *current = hm->buckets[i];
		// Iterate through the buckets
		while (current) {
			// Call the callback at the bucket node
			callback(current->key, current->data); 
			current = current->next;
		}
	}
}

/// @brief Removes a key-data pair from the hash map
/// @param hm Pointer to the HashMap structure
/// @param key The key string to remove
/// @param destroy_data Callback function to free the data associated with the key
void remove_data(HashMap * hm, char * key, DestroyDataCallback destroy_data) {
	size_t index = hash(hm, key); 
	Bucket *current = hm->buckets[index];
	Bucket *prev = NULL;

	// Iterate over linked list to find the key to delete
	while (current) {
		if (strcmp(current->key, key) == 0) {
			// if key is found, unlink the bucket from the list
			if (prev) {
				prev->next = current->next;
			} 
			else {
				// update header point
				hm->buckets[index] = current->next;
			}
			//checking if the function pointer isn't NULL to avoid secmentation faults
			if (destroy_data) {
    			destroy_data(current->data);
			}
			// free up duplicated key string and bucket node
			free(current->key);
			free(current);
			return;
		}
		// if key not found, update node pointer and go to the next bucket in the list
		prev = current;
		current = current->next;
	}
}

/// @brief Deletes the entire hash map, freeing all memory
/// @param hm Pointer to the HashMap structure to delete
/// @param destroy_data Callback function to free each data element
void delete_hashmap(HashMap * hm, DestroyDataCallback destroy_data) {
	// Iterate through the hashmap
	for (size_t i = 0; i < hm->size; i++) {
		Bucket *current = hm->buckets[i];
		// Iterate and delete each bucket in the list
		while (current) {
			Bucket *next = current->next;
			//checking if the function pointer isn't NULL to avoid secmentation faults
			if (destroy_data) {
    			destroy_data(current->data);
			}
			free(current->key);
			free(current);
			current = next;
		}
	}
	// Free the array of buckets and hashmap structure
	free(hm->buckets); 
	free(hm); 
}
