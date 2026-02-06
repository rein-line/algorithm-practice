// p6.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <stdlib.h>
#include <string.h> //strlen関数を使うのに必要
#include <windows.h>
#include <windows.h> // タイマーに必要
#include <mmsystem.h> 

typedef struct cell
{
    char* score;
    int id;
    struct cell* next;
} cell;
// ハッシュテーブル
typedef struct hashtable
{
    int size, count;
    cell** table;
} hashtable;
hashtable* make_hashtable(int size)
{
    hashtable* ht = (hashtable*)malloc(sizeof(hashtable));
    if (ht != NULL) {
        ht->size = size;
        ht->count = 0;
        ht->table = (cell**)malloc(sizeof(cell*) * size);
        if (ht->table == NULL) {
            free(ht);
            return NULL;
        }
        for (int i = 0; i < size; i++) ht->table[i] = NULL;
    }
    return ht;
}
int hash_func(hashtable* ht, const char* score) {
    unsigned int value = 0;
    for (int n = 0; score[n] != '\0'; n++)
        value = (value << 3) + score[n];
    return value % ht->size;
}
cell* make_cell(const char* score, int id, cell* next) {
    cell* cp = (cell*)malloc(sizeof(cell));
    if (cp != NULL) {
        cp->score = (char*)malloc(strlen(score) + 1);
        strcpy_s(cp->score, 16, score);
        cp->id = id;
        cp->next = next;
    }
    return cp;
}
// 挿入
bool insert_hash(hashtable* ht, const char* score, int id) 
{
    int hval = hash_func(ht, score);
    ht->table[hval] = make_cell(score, id, ht->table[hval]);
    ht->count++;
    return true;
}
void print_hashtable(hashtable* ht)
{
    int size = ht->size;
    for (int i = 0; i < size; i++)
    {
        printf("hval:%d score:", i);
        cell* cp = ht->table[i];
        for (; cp != NULL; cp = cp->next)
        {
            printf("%s", cp->score);
        }
        printf("\n");
    }
}
int search_hash(hashtable* ht, const char* score)
{
    int havl = hash_func(ht, score);
    cell* cp = ht->table[havl];
    for (; cp != NULL; cp = cp->next)
    {
        if (strcmp(cp->score, score) == 0)
        {
            printf("score = %s id = %d", cp->score, cp->id);
        }
    }
    return 0;
}
void hash_test0() 
{
    hashtable* ht = make_hashtable(100003);
    const char* ele[5] = { "ikaho", "numata", "kusatsu", "mizusawa", "haruna" };
    for (int i = 0; i < 5; i++)
    {
        printf("%s:%d\n", ele[i], hash_func(ht, ele[i]));
    }
}
void hash_test1(int num_data)
{
    hashtable* ht = make_hashtable(100003);
    char buff[12];
    int id = 0;
    for (int i = 0; i < num_data; i++)
    {
        sprintf_s(buff, "%d", rand()*rand());
        insert_hash(ht, buff, id);
        id++;
    }
}
void hash_test2()
{
    FILE* fpi;
    fopen_s(&fpi, "data_small.txt", "r");
    if (fpi == NULL)
    {
        printf("ファイルが見つかりません。\n");
        exit;
    }
    int data[50] = { 0 };
    for (int i = 0; i < 50; i++) 
    {
        if (fpi != 0)
        {
            fscanf_s(fpi, "%d", &data[i]);
        }
    }
    hashtable* ht = make_hashtable(17);
    char buff[12];
    for (int i = 0; i < 50; i++) 
    {
        sprintf_s(buff, "%d", data[i]);
        insert_hash(ht, buff, i);
    }
    print_hashtable(ht);
}
int main()
{
    hashtable* ht;
    const char* a = ;
    search_hash(ht, a);
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
