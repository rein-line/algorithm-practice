// p10.4.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h> // タイマーに必要
#include <mmsystem.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

long long Bproduct(int X[], int Y[], int n) {
	long long sum = 0;
	long power = 1;
	for (int i = 0; i < n; i++)
	{
		long long s = 0;
		long long p = power;
		for (int j = 0; j < n; j++) {
			s = s + p * X[i] * Y[j];
			p = p * 10;
		}
		sum = sum + s;
		power = power * 10;
	}
	return sum;
}

//アルゴリズム7.2
long long Product(int X[], int Y[], int n) 
{
	if (n == 1) return X[0] * Y[0];
	int h = n / 2;
	int* X12 = (int*)malloc(sizeof(int) * h);
	int* Y12 = (int*)malloc(sizeof(int) * h);
	for (int i = 0; i < h; i++) 
	{
		X12[i] = X[i] + X[i + h];
		Y12[i] = Y[i] + Y[i + h];
	}
	long long c = Product(&X[0], &Y[0], h);
	long long b = Product(X12, Y12, h);
	long long a = Product(&X[h], &Y[h], h);
	free(X12);
	free(Y12);
	return a * pow(10, n) + (b - (a + c)) * pow(10, n / 2) + c;
}

int main()
{
	//積を計算したい整数の入力
	int X[] = {7, 7, 7, 7, 7, 7, 7, 7};
	int Y[] = {9, 9, 9, 9, 9, 9, 9, 9};
	int size = COUNTOF(X);
	if ((size & (size - 1))) {
		printf("Size is not a power of 2. \n");
		exit(0);
	}
	//タイマー開始
	LARGE_INTEGER    frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER    start, end;
	QueryPerformanceCounter(&start);
	int repeat = 10000000;
	long long prod;
	for (int i = 0; i < repeat; i++) {
		prod = Product(X, Y, 8);
	}
	//タイマー終了計算時間出力
	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	printf("used time = %13.12lf \n", sec / 10000000);
    //値の出力
	printf("Summation = %lld",prod);
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
