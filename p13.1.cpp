// p13.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h> // タイマーに必要
#include <mmsystem.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define N_COFFEE 30 // Number of coffee types
#define W 160 // Weight
typedef struct{
    int Id;
    char Name[100];
    int w;
    int v;
    float z;
} CofeeTable;
typedef struct{
    int v;
    int x[N_COFFEE + 1];     // X[0] is NOT used.
} Table;
void ClearTable(Table T[][W + 1]) {
    for (int i = 0; i <= N_COFFEE; i++) {
        for (int j = 0; j <= W; j++) {
            T[i][j].v = 0;
            for (int k = 0; k <= N_COFFEE; k++)
                T[i][j].x[k] = 0;
        }
    }
}
void PrintTable(Table T[][W + 1]) {
    for (int i = 1; i <= N_COFFEE; i++) {
        for (int j = 1; j <= W; j++) {
            printf("\nT[%d][%d].v=%d\t", i, j, T[i][j].v);
            for (int k = 1; k <= N_COFFEE; k++)
                printf("%d", T[i][j].x[k]);
        }
        printf("\n");
    }
}
int ReadTable(CofeeTable T[]) {
    FILE* fp;
    const char* fname = "coffee_30types.csv";
    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Not open %s\n", fname);
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while ((fscanf(fp, "%d,%[^,],%d,%d", &(T[i].Id), T[i].Name,
        &(T[i].w), &(T[i].v))) != EOF)
        i = i + 1;
    fclose(fp);
    return i - 1;
}
void PrintCoffeeTable(CofeeTable T[], int size) {
    for (int i = 1; i <= size; i++)
        printf("(%d) beans-%d, %-12s, %d[kg], %d[YEN]\n", i,
            T[i].Id, T[i].Name, T[i].w, T[i].v);
    printf("\n");
}

//アルゴリズム8.5
void Knapsack_DP(CofeeTable T81[], Table T[N_COFFEE + 1][W + 1]) {
    Table T1, T2;
    ClearTable(T);
    for (int i = 1; i <= N_COFFEE; i++) 
    {
        for (int j = 1; j <= W; j++) 
        {
            T[i][j] = T[i - 1][j];
            if (j >= T81[i].w) 
            {
                T1 = T[i - 1][j - T81[i].w];
                T2 = T[i - 1][j];
                if (T1.v + T81[i].v > T2.v) 
                {
                    T1.v = T1.v + T81[i].v;
                    T1.x[i] = 1;
                    T[i][j] = T1;
                }
                else T[i][j] = T2;
            }
            else T[i][j] = T[i - 1][j];
        }
    }
}
//アルゴリズム8.4
int Knapsack(int C, CofeeTable T[], int X[], int size)
{
    int vmax = 0;
    for (int i = 1; i <= 1 << size; i++) {
        int wsum = 0, vsum = 0;
        for (int j = 1; j <= size; j++) {
            int z = (i - 1) >> (j - 1) & 1;
            wsum += z * T[j].w;
            vsum += z * T[j].v;
        }
        if (wsum <= C && vsum > vmax) {
            vmax = vsum;
            for (int j = 1; j <= size; j++) {
                int z = (i - 1) >> (j - 1) & 1;
                X[j] = z;
            }
        }
    }
    return vmax;
}
int main()
{
    CofeeTable T81[N_COFFEE + 1];
    int size = ReadTable(T81);
    int X[N_COFFEE + 1];
    PrintCoffeeTable(T81, size);
    Table T[N_COFFEE + 1][W + 1];
    LARGE_INTEGER    frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER    start, end;
    QueryPerformanceCounter(&start);

    //Knapsack(W, T81, X, N_COFFEE);
    Knapsack_DP(T81, T);
    //long long sum = Simple_Sum(D, D_SIZE);

    QueryPerformanceCounter(&end);
    LONGLONG span = end.QuadPart - start.QuadPart;
    double sec = (double)span / (double)frequency.QuadPart;
    printf("used time = % lf \n", sec);
    Knapsack_DP(T81, T);
    PrintTable(T);
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
