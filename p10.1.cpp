// p10.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h> // タイマーに必要
#include <mmsystem.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

long long Recurs_Sum2(int D[], int left, int right)
{
    int mid = (left + right) / 2;
    if (left == right)
    {
        return D[mid];
    }
    long long x = Recurs_Sum2(D, left, mid);
    long long y = Recurs_Sum2(D, mid + 1, right);
    return x + y;
}
long long Simple_Sum(int *D, int D_SIZE)
{
    long long sum = 0;
    for (int i = 0; i < D_SIZE; i++)
    {
        sum = sum + D[i];
    }
    return sum;
}
int main()
{
    FILE* fpi;
    fopen_s(&fpi, "random_150k.txt", "r");
    if (fpi == NULL)
    {
        printf("ファイルが見つかりません。\n");
        return -1;
    }
    int D_SIZE = 150000;
    int *D = (int *)malloc(sizeof(int)*D_SIZE);
    for (int i = 0; i < D_SIZE; i++)
    {
        fscanf_s(fpi, "%d", &D[i]);
    }
    LARGE_INTEGER    frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER    start, end;
    QueryPerformanceCounter(&start);

    long long sum = Recurs_Sum2(D, 0, D_SIZE - 1);
    //long long sum = Simple_Sum(D, D_SIZE);
    
    QueryPerformanceCounter(&end);
    LONGLONG span = end.QuadPart - start.QuadPart;
    double sec = (double)span / (double)frequency.QuadPart;
    printf("used time = % lf \n", sec);

    printf("Summation = %lld", sum);
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
