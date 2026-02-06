// p4.3.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h> // タイマーに必要
#include <mmsystem.h> // タイマーに必要
#include <math.h>

int main(){
    int n, sum = 0, t1 = 0, t2 = 0;
    scanf_s("%d", &n);
    LARGE_INTEGER    frequency;
    QueryPerformanceFrequency(&frequency);
    // 計算の開始時にカウンタ値を記録
    LARGE_INTEGER    start, end;
    QueryPerformanceCounter(&start);
    for (int i = 0;i<n ; i++){
        
        if (i < 2){
            sum = 1;
        }
        else{
            for (int j = 0; j < i; j++){
                if (j < 2){
                    sum = 1;
                }
                t1 = t2;
                t2 = sum;
                sum = t1 + t2;
            }
        }
        printf("n=%d:%d\n", i + 1, sum);
    }
    QueryPerformanceCounter(&end);
    // 経過時間を計算
    LONGLONG span = end.QuadPart - start.QuadPart;
    double sec = (double)span / (double)frequency.QuadPart;
    printf("used time = %16.14lf \n", sec);
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
