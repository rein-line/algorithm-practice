

// p7.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h> // タイマーに必要
#include <mmsystem.h> 
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

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
void swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}
void SelectionSort(int D[], int D_SIZE) 
{
    int max, ele;
    for (int i = D_SIZE - 1;i >0; i--)
    {
        ele = 0;
        max = D[ele];
        for (int j = 1; j <= i; j++)
        {
            if (D[j] >= max)
            {
                ele = j;
                max = D[ele];
            }
        }
        swap(&D[ele], &D[i]);
    }
    return;
}
// 挿入ソートAlgorithm 5.2
void InsertionSort(int D[], int D_SIZE) 
{
    for (int i = 1; i < D_SIZE; i++) 
    {
        int x = D[i];
        int j = i;
        while (D[j - 1] > x && j > 0)
        {
            D[j] = D[j - 1];
            j--;
        }
        D[j] = x;
    }
    return;
}
int main()
{
    int D_SIZE = 200000;
    FILE* fpi;
    FILE* fpw;
    fopen_s(&fpi, "result5.txt", "r");
    if (fpi == NULL)
    {
        printf("ファイルが見つかりません。\n");
        return -1;
    }
    int D[200000] = { 0 };
    for (int i = 0; i < D_SIZE; i += 10) 
    {
        fscanf_s(fpi, "%d %d %d %d %d %d %d %d %d %d", &D[i], &D[i+1], &D[i+2], &D[i+3], &D[i+4], &D[i+5], &D[i+6], &D[i+7], &D[i+8], &D[i+9]);
    }

    LARGE_INTEGER    frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER    start, end;
    QueryPerformanceCounter(&start);

    SelectionSort(D, D_SIZE);

    QueryPerformanceCounter(&end);
    LONGLONG span = end.QuadPart - start.QuadPart;
    double sec = (double)span / (double)frequency.QuadPart;
    printf("used time = % lf \n", sec);

    //PrintD(D, D_SIZE);
    
    printf("hash value = %d\n", hash_func(D, D_SIZE));
    //free(D);

    printf("%d\n", hash_func(D, D_SIZE));

    fopen_s(&fpw, "result6.txt", "w");
    if (fpw == NULL)
    {
        printf("ファイルが見つかりません。\n");
        return -1;
    }
    for (int i = 0; i < D_SIZE; i++) 
    {
        fprintf(fpw, "%2d \n", D[i]); 
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
