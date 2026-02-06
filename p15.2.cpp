// p15.2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<Windows.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#define PRINTG(GRAPH)                                          \
  do {                                                         \
    printf(#GRAPH "\n");                                       \
    PringGraph((int *)GRAPH, sizeof(GRAPH) / sizeof(GRAPH[0]), \
               sizeof(GRAPH[0]) / sizeof(GRAPH[0][0]));               \
  } while (0);

void PringGraph(int g[], int row, int column) {
	for (int i = 1; i < row; i++) {
		printf("%d ", i);
		for (int j = 1; j < column; j++)
			if (g[i * column + j] != 0) printf("-> %d", j);
		printf("\n");
	}
	printf("---\n");
}
#define NODE 11
float G[][NODE] = {
	//  0   1   2   3   4   5   6   7   8   9   10
	  { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },//0
	  { 0,  0, 33,  0,  0,  9,  0,  0, 12,  0,  0 },//1
	  { 0, 33,  0, 21,  7,  0,  0, 16,  0,  0, 13 },//2
	  { 0,  0, 21,  0, 13, 25,  0,  0, 14, 11,  0 },//3
	  { 0,  0,  7, 13,  0,  0,  5,  0,  0,  0,  0 },//4
	  { 0,  9,  0, 25,  0,  0, 16, 22,  0, 18,  0 },//5
	  { 0,  0,  0,  0,  5, 16,  0, 17, 20,  0, 27 },//6
	  { 0,  0, 16,  0,  0, 22, 17,  0,  0,  0,  0 },//7
	  { 0, 12,  0, 14,  0,  0, 20,  0,  0,  0, 21 },//8
	  { 0,  0,  0, 11,  0, 18,  0,  0,  0,  0,  0 },//9
	  { 0,  0, 13,  0,  0,  0, 27,  0, 21,  0,  0 },//10
};
float D[NODE];

void SetINFINITY_D() {
	for (int i = 1; i < NODE; i++) D[i] = INFINITY;
}
int S[NODE];
void SetEmpty_S() {
	for (int i = 1; i < NODE; i++) S[i] = 0;
}
void AddSET_S(int s) { S[s] = 1; }
void PrintSD() {
	for (int i = 1; i < NODE; i++) printf("%4d ", i);
	printf("\n");
	for (int i = 1; i < NODE; i++) printf("%4d ", S[i]);
	printf("\n");
	for (int i = 1; i < NODE; i++) printf("%4.1f ", D[i]);
	printf("\n---\n");
}
int FindMinVk() {
	int k = 0, min = 100;
	for (int i = 1; i < NODE; i++) {
		if (S[i] == 0 && min > D[i]) {
			k = i; min = D[i];
		}
	}
	return k;
}
// Algorithm 10.3
void Dijkstra103(float G[][NODE], int s) {
	SetINFINITY_D();
	SetEmpty_S();
	D[s] = 0;
	for (int i = 1; i < NODE; i++) {
		int k = FindMinVk();
		S[k] = 1;
		for (int j = 1; j < NODE; j++) {
			if (G[k][j] != 0 && S[j] == 0) {
				D[j] = fminf(D[j], D[k] + G[k][j]);
			}
		}
	}
}
int main() {
	PRINTG(G);
	Dijkstra103(G, 7);
	PrintSD();
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
