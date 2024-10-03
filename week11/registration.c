#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 131072

typedef struct name {
    char name[21];
    int count;
} cell_t;

typedef struct hash {
    cell_t* cell;
} hash_t;


unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash & (MAX_SIZE - 1);
}

// Extract base name and numeric suffix
int get_suffix(char *base_name, char *name) {
    int len = strlen(name);
    int i = len - 1;
    while (i >= 0 && isdigit(name[i])) {
        i--;
    }

    if (i == len - 1) {
        strcpy(base_name, name);  // No numeric suffix
        return -1;
    }
    strncpy(base_name, name, i + 1);
    base_name[i + 1] = '\0';

    return atoi(name + i + 1);  // Extract numeric suffix
}

void add(hash_t *table, char *name) {
    unsigned long idx = hash(name);
    unsigned long i = 0;
    
    while (table->cell[idx].count != 0 && strcmp(table->cell[idx].name, name) != 0) {
        i++;
        idx = (idx + i * i) % MAX_SIZE;  // Quadratic probing
    }
    strcpy(table->cell[idx].name, name);
    table->cell[idx].count = 1;
}

// Check if name is in hash table
bool is_in(hash_t *table, char *name) {
    unsigned long idx = hash(name);
    unsigned long i = 0;

    while (table->cell[idx].count != 0) {
        if (strcmp(table->cell[idx].name, name) == 0) {
            return true;
        }
        i++;
        idx = (idx + i * i) % MAX_SIZE;  // Quadratic probing
    }
    return false;
}

// Initialize hash table
hash_t* init_table() {
    hash_t *table = (hash_t*)malloc(sizeof(hash_t));
    table->cell = (cell_t*)calloc(MAX_SIZE, sizeof(cell_t));
    return table;
}

int main() {
    int n, suff;
    char name[21], base_name[21];
    hash_t *table = init_table();

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        suff = get_suffix(base_name, name);
        if (!is_in(table, name)) {
            printf("OK\n");
            add(table, name);
        } else {
            char new_name[21];
            int count = 1;
            while (true) {
                snprintf(new_name, sizeof(new_name), "%s%d", base_name, count);
                if (!is_in(table, new_name)) {
                    break;
                }
                count++;
            }
            printf("Change to %s\n", new_name);
            add(table, new_name);
        }
    }

    free(table->cell);
    free(table);

    return 0;
}
