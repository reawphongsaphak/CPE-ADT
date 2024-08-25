#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

typedef struct node {
    int town;
    int thief;
    struct node* parent;
    struct node* next_sibling;
    struct node* first_child;
} city_t;

city_t* map[MAX];

city_t* add_town(city_t* city, int parent, int town, int thief){
    city_t* newTown = (city_t*)malloc(sizeof(city_t));
    newTown->town = town;
    newTown->thief = thief;
    newTown->parent = NULL; newTown->next_sibling = NULL; newTown->first_child = NULL;

    city_t* pos = map[parent];
    newTown->parent = map[parent];
    newTown->next_sibling = pos->first_child;
    pos->first_child = newTown;
    map[town] = newTown;
    return city;
}

int solve(city_t* t, int remain_num) {
    if (t == NULL) {
        return 0;
    }
    int max_town = (t->town != 0)?1:0;
    city_t* child = t->first_child;
    while (child != NULL){
        if (child->thief == 1 && remain_num > 0) {
            max_town += solve(child, remain_num - 1);
        } else if (child->thief == 0) {
            max_town += solve(child, remain_num);
        }
        child = child->next_sibling;
    }
    return max_town;
}

void dfs(city_t* city){
    if (city == NULL){
        return;
    }
    else{ printf("city : %d\n",city->town);}
    dfs(city->first_child);
    dfs(city->next_sibling);
    return;
}

int main(){
    int town_in_city, parent, n_town, thief, money;
    city_t* city = (city_t*)malloc(sizeof(city_t));
    *city = (city_t){0, 0, NULL, NULL, NULL};
    map[0] = city;
    scanf("%d %d", &town_in_city, &money);

    for (int i = 0; i < town_in_city; i++){
        scanf("%d %d %d", &parent, &n_town, &thief);
        city = add_town(city, parent, n_town, thief);
    }
    // dfs(city);
    printf("%d\n", solve(city, money));
    return 0;
}