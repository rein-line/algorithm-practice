// p12.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define NUMTYPE 10
#define CAPACITY 40

typedef struct{
    int Id;
    char Name[100];
    int w;
    int v;
    float z;
} Table;

void Sort(Table T[], int size) {
    for (int i = 1; i <= size; i++) {
        Table base = T[i];
        int j = i;
        while (j > 1 && T[j - 1].z < base.z)
        {
            T[j] = T[j - 1];
            j--;
        }
        T[j] = base;
    }
    return;
}

int ReadTable(Table Table[]) {
    FILE* fp;
    const char* fname = "coffee_10types.csv";
    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Not open %s\n", fname);
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while ((fscanf(fp, "%d,%[^,],%d,%d", &(Table[i].Id),
        Table[i].Name, &(Table[i].w), &(Table[i].v))) != EOF) {
        Table[i].z = (float)Table[i].v / (float)Table[i].w;
        i = i + 1;
    }
    fclose(fp);
    return i - 1;
}

void PrintTable(Table T[], int size) {
    for (int i = 1; i <= size; i++)
        printf("(%d) beans - %d, % 12s, %d[kg], %d[YEN], %7.2f[YEN / Kg]\n", i, T[i].Id, T[i].Name, 
            T[i].w, T[i].v, T[i].z);
    printf("\n");
}

//アルゴリズム8.1
void GreedyKnapsack(int C, float X[], Table T[], int size) {
    Sort(T, size);
    for (int i = 1; i <= size; i++) {
        X[i] = 0;
    }
    int j = 1, sum = 0;
    while (sum < C) {
        if (T[j].w <= C - sum) {
            X[j] = 1;
            sum += T[j].w;
        }
        else {
            X[j] = (float)(C - sum) / T[j].w;
            sum = C;
        }
        j++;
    }
}
int main(int argc, const char* argv[]) {
    Table T81[NUMTYPE + 1];// T81[0] is NOT used.
    float X[NUMTYPE + 1];
    int size = ReadTable(T81);
    PrintTable(T81, size);
    GreedyKnapsack(CAPACITY, X, T81, size);
    PrintTable(T81, size);
    for (int i = 1; i <= size; i++) {
        printf("%s  %lf  \n", T81[i].Name, X[i]);
    }
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
