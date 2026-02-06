// p9.1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
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
int Partition(int D[], int left, int right){
    int k = (left + right) / 2;
    swap(&D[k], &D[right]);
    int i = left;
    int j = right - 1;
    while (i <= j) {
        while (D[i] < D[right]) {
            i = i + 1;
        }
        while (D[j] >= D[right] && j >= i) {
            j = j - 1;
        }
        if (i < j) {
            swap(&D[i], &D[j]);
        }
    }
    swap(&D[i], &D[right]);
    return i;
}
void QuickSort(int D[], int left, int right) {
    if (left < right) {
        int pivot_index = Partition(D, left, right);
        QuickSort(D, left, pivot_index - 1);
        QuickSort(D, pivot_index + 1, right);
    }
}
int main()
{
    FILE* fpi;
    fopen_s(&fpi, "random_200k.txt", "r");
    if (fpi == NULL)
    {
        printf("ファイルが見つかりません。\n");
        return -1;
    }
    int D_SIZE = 200000;
    int D[200000] = { 0 };
    for (int i = 0; i < D_SIZE; i++)
    {
        fscanf_s(fpi, "%d", &D[i]);
    }
    LARGE_INTEGER    frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER    start, end;
    QueryPerformanceCounter(&start);

    QuickSort(D, 0, D_SIZE - 1);

    QueryPerformanceCounter(&end);
    LONGLONG span = end.QuadPart - start.QuadPart;
    double sec = (double)span / (double)frequency.QuadPart;
    printf("used time = % lf \n", sec);

    //ソート後の配列に対するハッシュ値
    printf("hash value = %d", hash_func(D, D_SIZE));
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
