#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_PRODUCTS 50
#define MAX_FRIENDS 10

typedef struct {
    char name[50];
    int purchase_count;
} Product;

typedef struct {
    char username[50];
    char password[50];
    int friends[MAX_FRIENDS]; // 存储朋友的用户 ID
    int purchased[MAX_PRODUCTS]; // 存储购买的商品数量
} User;

User users[MAX_USERS];
Product products[MAX_PRODUCTS];
int user_count = 0, product_count = 0;

void register_user();
void login();
void add_product();
void recommend_products(int user_id);
void save_data();
void load_data();

int main() {
    load_data();
    int choice;
    while (1) {
        printf("\n1. 注册用户\n2. 登录\n3. 添加商品\n4. 退出\n选择操作: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: register_user(); break;
            case 2: login(); break;
            case 3: add_product(); break;
            case 4: save_data(); exit(0);
            default: printf("无效选择\n");
        }
    }
    return 0;
}

void register_user() {
    if (user_count >= MAX_USERS) {
        printf("用户数量已满\n");
        return;
    }
    printf("输入用户名: ");
    scanf("%s", users[user_count].username);
    printf("输入密码: ");
    scanf("%s", users[user_count].password);
    memset(users[user_count].purchased, 0, sizeof(users[user_count].purchased));
    user_count++;
    printf("注册成功！\n");
}

void login() {
    char username[50], password[50];
    printf("输入用户名: ");
    scanf("%s", username);
    printf("输入密码: ");
    scanf("%s", password);
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("登录成功！\n");
            recommend_products(i);
            return;
        }
    }
    printf("用户名或密码错误\n");
}

void add_product() {
    if (product_count >= MAX_PRODUCTS) {
        printf("商品数量已满\n");
        return;
    }
    printf("输入商品名称: ");
    scanf("%s", products[product_count].name);
    products[product_count].purchase_count = 0;
    product_count++;
    printf("商品添加成功！\n");
}

void recommend_products(int user_id) {
    int recommendations[MAX_PRODUCTS] = {0};
    for (int i = 0; i < MAX_FRIENDS; i++) {
        int friend_id = users[user_id].friends[i];
        if (friend_id >= 0 && friend_id < user_count) {
            for (int j = 0; j < MAX_PRODUCTS; j++) {
                recommendations[j] += users[friend_id].purchased[j];
            }
        }
    }
    printf("推荐商品:\n");
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        if (recommendations[i] > 0) {
            printf("%s (推荐度: %d)\n", products[i].name, recommendations[i]);
        }
    }
}

void save_data() {
    FILE *file = fopen("data.dat", "wb");
    fwrite(&user_count, sizeof(int), 1, file);
    fwrite(users, sizeof(User), user_count, file);
    fwrite(&product_count, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), product_count, file);
    fclose(file);
}

void load_data() {
    FILE *file = fopen("data.dat", "rb");
    if (!file) return;
    fread(&user_count, sizeof(int), 1, file);
    fread(users, sizeof(User), user_count, file);
    fread(&product_count, sizeof(int), 1, file);
    fread(products, sizeof(Product), product_count, file);
    fclose(file);
}
