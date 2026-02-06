// p8.3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // タイマーに必要
#include <mmsystem.h> 

#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

typedef struct record {
    char name[20];
    double data[2];
}record;

void PrintD(int D[], int D_SIZE) {
    for (int i = 0; i < D_SIZE; i++) {
        printf("%2d  ", D[i]);
    }
    printf("\n");
}
int hash_func(int D[], int D_SIZE) {
    char buff[12];
    unsigned int value = 1;
    for (int i = 0; i < D_SIZE; i++) {
        sprintf_s(buff, "%d", D[i]);
        for (int n = 0; buff[n] != '\0'; n++) {
            int temp = (buff[n] * (i + 77)) % 6700417 + 1;
            value = ((value)*temp) % 6700417;
        }
    }
    return value;
}
void swap(record* a, record* b) {
    record temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}
void PushHeap(record T[], int* size, record x, int target) {

    *size += 1;
    T[*size] = x;
    int k = *size;
    while (T[k].data[target] > T[k / 2].data[target] && k > 1) 
    {
        swap(&T[k], &T[k / 2]);
        k /= 2;
    }

}
record DeleteMaxinum(record T[], int* size, int target) {
    record max;
    int k, big;
    max = T[1];
    T[1] = T[*size];
    T[*size].data[target] = 0;
    k = 1;
    while (2 * k <= *size) {
        if (2 * k == *size) {
            if (T[k].data[target] < T[2 * k].data[target]) {
                swap(&T[k], &T[2 * k]);
                k = 2 * k;
            }
            else break;
        }
        else {
            big = 2 * k;
            if (T[2 * k].data[target] < T[2 * k + 1].data[target]){
                big = 2 * k + 1;
            }
            if (T[k].data[target] < T[big].data[target]) {
                swap(&T[k], &T[big]);
                k = big;
            }
            else break;
        }
    }
    return max;
}

int main()
{
    FILE* fpi;
    fopen_s(&fpi, "todoufuken_data.txt", "r");
    if (fpi == NULL) 
    {
        printf("読み込みエラーです。¥n");
        return-1;
    }
    char name[10];
    double population;
    double area;
    int D_SIZE = 47;
    int target = 1; //0:population, 1:area
    record* D = (record*)(malloc(sizeof(record) * (D_SIZE+1)));
    if (D == NULL) {
        exit(1);
    }
    for (int i = 1; i <= 47; i++) {
        fscanf_s(fpi, "%s %lf %lf", name, 10, &population, &area);
        strcpy_s(D[i].name, 10, name);
        D[i].data[0] = population;
        D[i].data[1] = area;
    }
    record* T = (record*)(malloc(sizeof(record) *(D_SIZE + 1)));
    if (T != NULL) {
        for (int i = 0; i <= D_SIZE; i++) {
            T[i].data[0] = 0;
            T[i].data[1] = 0;
        }
    }
    int size = 0;
    for (int i = 1; i <= D_SIZE; i++) {
        PushHeap(T, &size, D[i], target);
    }
    for (int i = D_SIZE - 1; i >= 0; i = i - 1) {
        D[i] = DeleteMaxinum(T, &size, target);
    }
    for (int i = 0; i < 47; i++)
    {
        printf("%s %lf %lf\n", D[i].name, D[i].data[0], D[i].data[1]);
    }
    free(D);
    free(T);
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
