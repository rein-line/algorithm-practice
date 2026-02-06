// p14.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#pragma warning(disable:4996)
#include <setjmp.h>
jmp_buf env;
#define COUNTOF(array) ( sizeof (array ) / sizeof (array [0]))

void PrintA(int Y[], int n) {
    for (int i = 1; i <= n; i++)printf("%4d\t", Y[i]);
    printf("\n");
}
void ClearA(int M[], int n) {
    for (int i = 0; i <= n; i++) M[i] = 0;
}

//アルゴリズム9.2
void BB_subsetsum(int s, int level, int X[], int Y[], int n) {
    if (level > n) {
        int sum = 0;
        for (int i = 1; i <= n; i++)sum = sum + Y[i] * X[i];
        if (sum == s) {
            PrintA(Y, n); longjmp(env, 1);
        }

    }
    else {
        int sum1 = 0; int sum2 = 0;
        for (int i = 1; i <= n; i++) {
            if (i < level) {
                sum1 = sum1 + X[i] * Y[i]; sum2 = sum1;
            }
            else {
                sum2 = sum2 + X[i];
            }

        }
        if (sum1 < s && sum2 >= s) {
            Y[level] = 0; BB_subsetsum(s, level + 1, X, Y, n);
            Y[level] = 1; BB_subsetsum(s, level + 1, X, Y, n);
        }
    }
    if (level == 1)printf("sに等しい並び方は存在しない。");
}
int main() {
    int X[] = { 0,1,12,4,8,9,11,13,17,7,21,15,2,23,6,31,10,3,18,19,5 };
    int sum = 223;
    int n = COUNTOF(X) - 1;
    int* Y = (int*)malloc(sizeof(int) * (n + 1));
    ClearA(Y, n);

    PrintA(X, n);
    if (!setjmp(env))BB_subsetsum(sum, 1, X, Y, n);
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
