// p9.2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h> // タイマーに必要
#include <mmsystem.h> 
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

typedef struct record {
	char city[50];
	char county[50];
	double data[20];
}record;

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
void PrintD(record D[], int D_SIZE, int target) {
    for (int i = 0; i < D_SIZE; i++) {
        printf("%s %s %lf\n　", D[i].city, D[i].county, D[i].data[target]);
    }
    printf("\n");
}
void swap(record* a, record* b) {
	record temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}
int Partition(record D[], int left, int right, int target) {
	int k = (left + right) / 2;
	swap(&D[k], &D[right]);
	int i = left;
	int j = right - 1;
	while (i <= j) {
		while (D[i].data[target] < D[right].data[target]) i++;
		while (D[j].data[target] >= D[right].data[target] && j >= i) j--;
		if (i < j)swap(&D[i], &D[j]);
	}
	swap(&D[i], &D[right]);
	return i;
}
void QuickSort(record D[], int left, int right, int target) {
	if (left < right) {
		int pivot_index = Partition(D, left, right, target);
		QuickSort(D, left, pivot_index - 1, target);
		QuickSort(D, pivot_index + 1, right, target);
	}
}
int main()
{
    FILE* fpi;
    fopen_s(&fpi, "city_population.txt", "r");
    if (fpi == NULL)
    {
        printf("ファイルが見つかりません。\n");
        return -1;
    }
    int D_SIZE = 1692;
    int target = 9;
    record* D = (record*)(malloc(sizeof(record) * D_SIZE));
    
    if (D == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < D_SIZE; i++) {
        fscanf_s(fpi, "%s %s %lf %lf %lf %lf %lf %lf %lf %lf %lf", &D[i].city, 50, &D[i].county, 50, &D[i].data[0], &D[i].data[1], &D[i].data[2], &D[i].data[3], &D[i].data[4], &D[i].data[5], &D[i].data[6], &D[i].data[7], &D[i].data[8], &D[i].data[9]);
    }
    for (int i = 0; i < D_SIZE; i++) {
        D[i].data[9] = D[i].data[7] / D[i].data[5];
    }
    QuickSort(D, 0, D_SIZE - 1, target);
    PrintD(D, D_SIZE, target);
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
