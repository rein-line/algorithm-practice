
// p11.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h> // タイマーに必要
#include <mmsystem.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
typedef struct record {
    char city[50];
    char county[50];
    double data[20];
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
        sprintf(buff, "%d", D[i]);
        for (int n = 0; buff[n] != '\0'; n++) {
            int temp = (buff[n] * (i + 77)) % 6700417 + 1;
            value = ((value)*temp) % 6700417;
        }
    }
    return value;
}
void swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}

//アルゴリズム7.3
void Merge(int D[], int M[], int left, int mid, int right) {
    int x = left, y = mid + 1;
    for (int i = 0; i <= right - left; i++) {
        if (x == mid + 1) {
            M[i] = D[y];
            y++;
        }
        else if (y == right + 1) {
            M[i] = D[x];
            x++;
        }
        else if(D[x]<=D[y]){
            M[i] = D[x];
            x++;
        }
        else {
            M[i] = D[y];
            y++;
        }
        
    }
    for (int i = 0; i <= right - left; i++) {
        D[left + i] = M[i];
    }
}
//アルゴリズム7.4
void MergeSort(int D[], int M[], int left, int right){
    int mid = (left + right) / 2;
    if (left < mid){
        MergeSort(D, M, left, mid);
    }
    if (mid + 1 < right) {
        MergeSort(D, M, mid + 1, right);
    }
    Merge(D, M, left, mid, right);
}


void Merge(record  D[], record M[], int left, int mid, int right, int target) {
    int x = left;
    int y = mid + 1;
    for (int i = 0; i <= right - left; i++) {
        if (x == mid + 1) {
            M[i] = D[y];
            y++;
        }
        else if (y == right + 1) {
            M[i] = D[x];
            x++;
        }
        else if (D[x].data[target] >= D[y].data[target]) {
            M[i] = D[x];
            x++;
        }
        else {
            M[i] = D[y];
            y++;
        }
    }
    for (int i = 0; i <= right - left; i++) {
        D[left + i] = M[i];
    }
}

void MergeSort(record D[], record M[], int left, int right, int target) {
    int mid = (left + right) / 2;
    if (left < mid)MergeSort(D, M, left, mid, target);
    if (mid + 1 < right)MergeSort(D, M, mid + 1, right, target);
    Merge(D, M, left, mid, right, target);
}

int main()
{
    FILE* fpi;
    fopen_s(&fpi, "city_population.txt", "r");
    if (fpi == NULL)
    {
        printf("ファイルが見つかりません。\n");
        return -1;
    }
    int D_SIZE = 1692;
    int target = 5;
    record* D = (record*)malloc(sizeof(record) * D_SIZE);
    record* M = (record*)(malloc(sizeof(record) * D_SIZE));    
    for (int i = 0; i <= D_SIZE; i++) {
        fscanf(fpi, "%s %s %lf %lf %lf %lf %lf %lf %lf %lf %lf", &D[i].city, &D[i].county, &D[i].data[0], &D[i].data[1], &D[i].data[2], &D[i].data[3], &D[i].data[4], &D[i].data[5], &D[i].data[6], &D[i].data[7], &D[i].data[8]);
        //printf("%s", D[i].county);
    }
    for (int i = 0; i < D_SIZE; i++) {
        D[i].data[9] = D[i].data[3] + D[i].data[4] + D[i].data[5] + D[i].data[6];
    }
    MergeSort(D, M, 0, D_SIZE - 1, target);

    /*LARGE_INTEGER    frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER    start, end;
    QueryPerformanceCounter(&start);

    MergeSort(D, M, 0, D_SIZE - 1);

    QueryPerformanceCounter(&end);
    LONGLONG span = end.QuadPart - start.QuadPart;
    double sec = (double)span / (double)frequency.QuadPart;
    printf("used time = % lf \n", sec);*/

    for (int i = D_SIZE - 1; i >= 0; i--) {
        printf("%d %30.30s %30.30s %10.5f\n", D_SIZE - i, M[i].city, M[i].county, M[i].data[target] / 4);
    }
    //printf("hash value = %d", hash_func(D, D_SIZE));
    free(D);
    fclose(fpi);
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
