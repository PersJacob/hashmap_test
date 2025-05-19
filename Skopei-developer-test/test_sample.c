#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"

size_t mystrlen(const char *str) {
    return strlen(str) + 1;
}

void print_element(const char *key, void *data) {
	printf("(\"%s\", %s)\n", key, (char*)data);
}

void *resolve_collision(void *old_value, void *new_value) {
	return new_value;
}

int main() {
	unsigned int key_space = 1024;
	HashMap * hm = create_hashmap(key_space);

	char * string_1 = "Jasper";
	char * string_2 = "Jens";
	char * string_3 = "Newby";
	char * string_4 = "Emil";
	const char * key_1    = "Electrical Engineer";
	const char * key_2    = "Software Engineer";
	const char * key_3    = "Embedded Software Engineer";
	const char * key_4    = "Product Owner";
	const char * key_5    = "Gardener";

	// Insert ("Electrical Engineer" -> "Jasper").
	insert_data(hm, key_1, string_1, resolve_collision);
	assert(memcmp(get_data(hm, key_1), string_1, mystrlen(string_1)) == 0);

	// Insert ("Software Engineer" -> "Jens").
	insert_data(hm, key_2, string_2, resolve_collision);
	assert(memcmp(get_data(hm, key_2), string_2, mystrlen(string_2)) == 0);

	// Insert ("Embedded Software Engineer" -> "Jasper").
	insert_data(hm, key_3, string_1, resolve_collision);
	assert(memcmp(get_data(hm, key_3), string_1, mystrlen(string_1)) == 0);

	// Insert ("Product Owner" -> "Emil").
	insert_data(hm, key_4, string_4, resolve_collision);
	assert(memcmp(get_data(hm, key_4), string_4, mystrlen(string_4)) == 0);

	// Insert ("Embedded Software Engineer" -> "Newby").
	insert_data(hm, key_3, string_3, resolve_collision);
	assert(memcmp(get_data(hm, key_3), string_3, mystrlen(string_3)) == 0);

	// Get data for a not inserted key.
	assert(get_data(hm, key_5) == NULL);

	// Iterate the hash map
	iterate(hm, print_element);

	// Delete key "Software Engineer".
	remove_data(hm, key_2, NULL);
	assert(get_data(hm, key_2) == NULL);
	
	// Delete key "Electrical Engineer".
	remove_data(hm, key_1, NULL);
	assert(get_data(hm, key_1) == NULL);

	// Delete key "Embedded Software Engineer".
	remove_data(hm, key_3, NULL);
	assert(get_data(hm, key_3) == NULL);

	// Delete key "Gardener".
	remove_data(hm, key_5, NULL);
	assert(get_data(hm, key_5) == NULL);

	// Delete the hash map.
	delete_hashmap(hm, NULL); 

	return 0;
}
