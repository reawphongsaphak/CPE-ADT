#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct cell {
    char original_text[50 + 1]; 
    char sorted_text[50 + 1];
} cell_t;

typedef struct table {
    cell_t *cell;
    int last_idx;
} table_t;

//* ==================   init table  ===================
table_t *init_table(int n) {
    table_t *table = (table_t*)malloc(sizeof(table_t));
    table->cell = (cell_t*)malloc(n * sizeof(cell_t));
    table->last_idx = 0;
    return table;
}

//* ===============    sort function   ==================
void merge(char *text, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    // Temporary arrays to hold parts of the string
    char L[n1 + 1], R[n2 + 1];
    // Copy data to temp arrays
    for (i = 0; i < n1; i++)
        L[i] = text[l + i];
    L[n1] = '\0';  // Null-terminate
    for (j = 0; j < n2; j++)
        R[j] = text[m + 1 + j];
    R[n2] = '\0';  // Null-terminate

    // Merge back to original string
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            text[k] = L[i];
            i++;
        } else {
            text[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        text[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        text[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(char *text, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(text, l, m);
        mergeSort(text, m + 1, r);
        merge(text, l, m, r);
    }
    return;
}

//* ====================== solve ======================
table_t *add(char *text, table_t *table) {
    strcpy(table->cell[table->last_idx].original_text, text);
    strcpy(table->cell[table->last_idx].sorted_text, text);
    mergeSort(table->cell[table->last_idx].sorted_text, 0, strlen(text) - 1);
    table->last_idx++;
    return table;
}

bool is_anagram(char *sorted_text1, char *sorted_text2) {
    return strcmp(sorted_text1, sorted_text2) == 0;
}

//* ================  main function  ==================
int main() {
    int n, m;
    char text1[50 + 1], text2[50 + 1];
    scanf("%d %d", &n, &m);
    table_t *table = init_table(n);

    for (int i = 0; i < n; i++) {
        scanf("%s", text1);
        table = add(text1, table);
    }

    for (int i = 0; i < m; i++) {
        scanf("%s", text2);
        char sorted_text2[50 + 1];
        strcpy(sorted_text2, text2);
        mergeSort(sorted_text2, 0, strlen(sorted_text2) - 1);

        for (int j = 0; j < table->last_idx; j++) {
            if (is_anagram(table->cell[j].sorted_text, sorted_text2)) {
                printf("%s ", table->cell[j].original_text);
            }
        }
        printf("\n");
    }

    // Free allocated memory
    free(table->cell);
    free(table);

    return 0;
}