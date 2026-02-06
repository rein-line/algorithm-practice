
// p15.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <stdio.h>
#define STACKSIZE 100
#define NODE 11      // 0--10

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
int stack[STACKSIZE], top;
void InitStack() {
	top = 0;
}
void Push(int x) {
	stack[top++] = x;
}
int Pop() {
	return stack[--top];
}
void PrintStack() {
	printf("\n Stack:");
	for (int i = 0; i < top; i++) printf("%d ", stack[i]);
	printf("\n");
}
int EmptyStack() {
	return !top;
}
int queue[STACKSIZE], head, tail;
void InitQueue() {
	head = tail = 0;
}
void Enqueue(int x) {
	queue[tail++] = x;
}
int Dequeue() {
	return queue[head++];
}
int EmptyQueue() {
	return head == tail;
}
void PrintQueue() {
	printf("\n Queue:");
	for (int i = head; i < tail; i++) printf("%d ", queue[i]);
	printf("\n");
}
int G[][NODE] = {
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
int C[NODE];
int InQ[NODE];
//アルゴリズム10.1
void BFS101(int G[][NODE], int s) {
	for (int i = 1; i < NODE; i++) C[i] = InQ[i] = 0;
	InitQueue();
	Enqueue(s); InQ[s] = 1;
	while (!EmptyQueue()) {
		int k = Dequeue();
		C[k] = 1;
		printf("%d ", k);
		for (int h = 1; h < NODE; h++) {
			if (G[k][h] != 0) {
				int val = G[k][h];
				if (InQ[h] == 0 && C[h] == 0)Enqueue(h); InQ[h] = 1;
			}
		}
	}
	printf("\n");
}

//アルゴリズム10.3
void DFS102(int G[][NODE], int s) {
	for (int i = 1; i < NODE; i++) C[i] = 0;
	InitStack();
	Push(s);
	while (!EmptyStack()) {
		int k = Pop();
		if (C[k] == 0) {
			//printf("%d", C[k]);
			C[k] = 1;
			//printf("%d", C[k]);
			printf("%d ", k);
			for (int h = 1; h < NODE; h++) {
				//printf("%d ", G[k][h]);
				if (G[k][h] != 0) {
					int val = G[k][h];
					if (C[h] == 0)Push(h);
				}
			}
		}
	}
}
int main() {
	PRINTG(G);
	BFS101(G, 7);
	DFS102(G, 7);
	return	0;
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
