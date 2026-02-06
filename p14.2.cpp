// p14.2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include<stdbool.h>
#include<Windows.h>
#pragma warning(disable:4996)
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define N_PAINTING 30 // Number of Painting

typedef struct {
	int Id;
	char Name[100];
	int w;
	int p;
	float v;
}PTable;

// global variable
PTable T91[N_PAINTING + 1];
const int n = N_PAINTING;
int X[N_PAINTING + 1];
int ZX[N_PAINTING + 1];
int z;
int c;

int ReadPTable() {
	FILE* fp;
	const char* fname = "paint_30types.csv";
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("Not open %s\n", fname);
		exit(EXIT_FAILURE);
	}
	int i = 1;
	while ((fscanf(fp, "%d,%[^,],%d,%d ", &(T91[i].Id), T91[i].Name, &(T91[i].w), &(T91[i].p))) != EOF) {
		T91[i].v = (float)T91[i].p / (float)T91[i].w;
		i = i + 1;
	}
	fclose(fp);
	return i - 1;
}
void PrintPTable() {
	for (int i = 1; i <= n; i++)
		printf("(%d) P-%d, %2s, %2d[Kg], %2d[YEN], %2f[YEN/kg]\n", i, T91[i].Id, T91[i].Name, T91[i].w, T91[i].p, T91[i].v);
	printf("\n");
}
void ClearX(int X[]) {
	for (int i = 0; i <= n; i++)X[i] = 0;
}
int SumW(int X[]) {
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += T91[i].w * X[i];
	return sum;
}
int SumP(int X[]) {
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += T91[i].p * X[i];
	return sum;
}
int Vmax(int level) {
	int Vmax = 0;
	for (int i = level; i <= n; i++) {
		if (T91[i].v > Vmax)Vmax = T91[i].v;
	}
	return Vmax;
}
#define CheckA (w > c)
#define CheckB (w == c)
#define CheckC (v + (c - w) * Vmax(level) < z)

//アルゴリズム9.3
void BB_01knapsack(int level) {
	int w = SumW(X);
	int v = SumP(X);
	if (level > n) {
		if (w <= c && v > z) {
			z = v;
			for (int i = 1; i <= n; i++)ZX[i] = X[i];
		}
	}else {
		if (w <= c) {
			if (w == c) {
				if (v > z) {
					z = v;
					for (int i = 1; i <= n; i++)ZX[i] = X[i];
				}
			}
			else if (v + (c - w) * Vmax(level) >= z) {
				X[level] = 1; BB_01knapsack(level + 1);
				X[level] = 0; BB_01knapsack(level + 1);
			}
		}
	}
}
int main(int argc, const char *argv[]) {
	if (ReadPTable() != n) {
		printf("Error\n");
		exit(0);
	}
	PrintPTable();
	ClearX(X); ClearX(ZX);
	z = 0; c = 150;
	//BB_01knapsack(1);

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER start, end;
	QueryPerformanceCounter(&start);

	BB_01knapsack(1);

	QueryPerformanceCounter(&end);
	LONGLONG span = end.QuadPart - start.QuadPart;
	double sec = (double)span / (double)frequency.QuadPart;
	printf("used time = %lf \n", sec);

	int sump = 0, sumw = 0;
	for (int i = 1; i <= n; i++) {
		sump += ZX[i] * T91[i].p;
		sumw += ZX[i] * T91[i].w;
	}
	printf("\n");
	for (int i = 1; i <= n; i++)printf("%d ", ZX[i]);
	printf("\tPrice=%d\tWeight=%d\n", sump, sumw);
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
