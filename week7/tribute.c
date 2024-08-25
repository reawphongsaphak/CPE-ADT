#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int town;
    int thief;
    struct node* parent;
    struct node* next_sibling;
    struct node* first_child;
}city_t;

city_t* find(city_t* city, int town){
    if (city == NULL || city->town == town){
        return city;
    }
    city_t*pos = find(city->first_child, town);
    if (pos != NULL){
        return pos;
    }
    else{return find(city->next_sibling, town);}
}

int dfs(city_t* city, int first_money,int money){
    if (city == NULL){
        return 0;
    }
    if (city->parent == NULL){
        return dfs(city->first_child, first_money,money) + dfs(city->next_sibling, first_money, money);
    }else if (city->parent->parent == NULL){
        money = first_money;
    }
    // printf("at town %d have money %d left\n", city->town, money);
    if (money - city->thief == -1){
        return dfs(city->next_sibling, first_money, money);
    }
    money = money - city->thief;
    return dfs(city->first_child, first_money,money) + dfs(city->next_sibling, first_money, money) + 1;
}

int solve(city_t* t, int remain_num) {
    if (t == NULL) {
        return 0;
    }
    int max_cities = (t->town != 0)?1:0;
    city_t* child = t->first_child;
    while (child != NULL){
        if (child->thief == 1 && remain_num > 0) {
            max_cities += solve(child, remain_num - 1);
        } else if (child->thief == 0) {
            max_cities += solve(child, remain_num);
        }
        child = child->next_sibling;
    }
    return max_cities;
}

void dfs1(city_t* city){
    if (city == NULL){
        return;
    }
    if(city->parent == NULL){
        printf("at root\n");
    }
    else{ printf("city : %d has parent %d\n",city->town, city->parent->town);}
    dfs1(city->first_child);
    dfs1(city->next_sibling);
    return;
}

city_t* add_town(city_t* city, int parent, int town, int thief){
    city_t* newTown = (city_t*)malloc(sizeof(city_t));
    newTown->town = town;
    newTown->thief = thief;
    newTown->parent = NULL; newTown->next_sibling = NULL; newTown->first_child = NULL;
    // if (city == NULL){
    //     return newTown;
    // }
    // city_t* pos = find(city, parent);
    // newTown->parent = pos;
    // if (pos->first_child == NULL){
    //     pos->first_child = newTown;
    //     return city;
    // }
    // city_t* temp = pos->first_child;
    // while (temp->next_sibling != NULL){
    //     temp = temp->next_sibling;
    // }
    // temp->next_sibling = newTown;
    city_t* pos = find(city, parent);
    newTown->parent = pos;
    newTown->next_sibling = pos->first_child;
    pos->first_child = newTown;
    return city;
}


int main(){
    int town_in_city, parent, n_town, thief, money;
    city_t* city = (city_t*)malloc(sizeof(city_t));
    *city = (city_t){0, 0, NULL, NULL, NULL};
    scanf("%d %d", &town_in_city, &money);

    for (int i = 0; i < town_in_city; i++){
        scanf("%d %d %d", &parent, &n_town, &thief);
        city = add_town(city, parent, n_town, thief);
    }
    // dfs1(city);
    printf("%d\n", solve(city, money));
    // printf("%d\n", dfs(city, money, money));
    return 0;
}

