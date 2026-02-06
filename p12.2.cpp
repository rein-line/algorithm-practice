// p12.2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <iostream>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define NUMTYPE 10
#define CAPACITY 40

typedef struct {
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

void GenerateZ(int Z[], int size) {
    for (int i = 1; i <= 1 << size; i++) {
        for (int j = size; j > 0; j--) {
            Z[i * (size + 1) + j] = (i - 1) >> (j - 1) & 1;
        }
    }
}

//アルゴリズム8.4
int Knapsack(int C, Table T[], int X[], int Z[], int size) {
    GenerateZ(Z, size);
    int vmax = 0;
    for (int i = 1; i <= 1 << size; i++) {
        int vsum = 0, wsum = 0;
        for (int j = 1; j <= size; j++) {
            wsum += Z[i * (size + 1) + j] * T[j].w;
            vsum += Z[i * (size + 1) + j] * T[j].v;
        }
        if (wsum <= C && vsum > vmax) {
            vmax = vsum;
            for (int j = 1; j <= size; j++) {
                X[j] = Z[i * (size + 1) + j];
            }
        }
    }
    return vmax;
}
void swap(Table* a, Table* b) {
    Table temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int main(void) {
    Table T81[NUMTYPE + 1];
    int X[NUMTYPE + 1]; // X[0] is NOT used.
    int Z[((1 << NUMTYPE) + 1) * (NUMTYPE + 1)];
    int size = ReadTable(T81);
    PrintTable(T81, size);

    int vmax = Knapsack(CAPACITY, T81, X, Z, size);
    PrintTable(T81, size);
    for (int i = 1; i <= size; i++) {
        printf("X%d = %d\t", i, X[i]);
    }
    printf("\n");
    printf("vmax = %d", vmax);
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
