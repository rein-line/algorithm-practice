// p5.2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#define N 200000

#include <iostream>
typedef struct node {
    int id;
    int score;
    node* left;
    node* right;
} node;

//木をたどって値を昇順に出力する
void print_value(FILE* fpw, node* now) {
    if (now == NULL) {
        return;
    }
    print_value(fpw, now->left);
    fprintf(fpw, "%d\n", now->score);
    print_value(fpw, now->right);
}
//木をたどってメモリを解放
void finish(node* p1) {
    if (p1 == NULL) {
        return;
    }
    finish(p1->left);
    finish(p1->right);
    free(p1);
}
//木を描く関数
void draw_tree(FILE* fpt, node* p1, float x, float y, float width) {
    if (p1 == NULL) return;
    int score = p1->score;
    fprintf(fpt, "%8.5f, %8.5f, %d \n", x, -y, score);
    width /= 2;
    draw_tree(fpt, p1->left, x-width, y + 1, width);
    fprintf(fpt, "%8.5f, %8.5f, %d \n", x, -y, score);
    draw_tree(fpt, p1->right, x+width, y + 1, width);
    width *= 2;
    fprintf(fpt, "%8.5f, %8.5f, %d \n", x, -y, score);
}
void maketree(node* p1, int id, int score) {
    //追加するノード
    node* p2;
    //親ノードより値(score)が大きい場合
    if (p1->score <= score) {
        //右がNULLならそこに新たなノードをぶら下げる 
        if (p1->right == NULL) {
            p2 = (node*)malloc(sizeof(node));
            p2->id = id;
            p2->score = score;
            p2->left = NULL;
            p2->right = NULL;
            p1->right = p2;
        }
        else {     // NULLでなければ右側のノードに移動してmake_tree()を実行する
            maketree(p1->right, id, score);
        }
    }
    else {
        //ここからは親ノードより値(score)が小さい場合
       //左がNULLならそこに新たなノードをぶら下げる 
        if (p1->left == NULL) {
            p2 = (node*)malloc(sizeof(node));
            p2->id = id;
            p2->score = score;
            p2->left = NULL;
            p2->right = NULL;
            p1->left = p2;
        }
        else {  // NULLでなければ左側のノードに移動してmake_tree()を実行する
            maketree(p1->left, id, score);
        }
    }
}

//木の高さを計算する関数
int height_tree(node *p1) {
    int hei;
    if (p1 == NULL){
        return 0;
    }
    int hei_left, hei_right;
    hei_left = height_tree(p1->left);
    hei_right = height_tree(p1->right);
    if (hei_left < hei_right){
        hei = hei_right + 1;
    }
    else {
        hei = hei_left + 1;
    }
    return hei;
}

int main(){
    FILE* fpi; //入力ファイル
    FILE* fpw; //昇順にソートしたファイル
    FILE* fpt; //木を描くためのファイル
    fopen_s(&fpi, "data_huge.txt", "r");
    fopen_s(&fpw, "order2.txt", "w");
    fopen_s(&fpt, "tree2.xls", "w");
    if (fpi == NULL){
        printf("入力ファイルが開けません。\n");
        return -1;
    }
    if (fpw == NULL){
        printf("出力ファイルが開けません。\n");
        return -1;
    }
    if (fpt == NULL){
        printf("出力ファイルが開けません。\n");
        return -1;
    }
    int data[N], i=0, temp_num;
    while ((fscanf_s(fpi, "%d", &data[i])) != EOF)
    {
        i++;
    }
    temp_num = i;
    node* p1; 
    p1 = (node*)malloc(sizeof(node));
    if (p1 == NULL)
    {
        printf("memory cannot alloc! \n");
    }
    p1->id = 0;
    p1->score = data[0];
    p1->left = NULL;
    p1->right = NULL;
    for (i = 0; i < temp_num; i++){
        maketree(p1, i, data[i]);
    }
    print_value(fpw, p1);
    draw_tree(fpt, p1, 0, 0, 1);
    int height;
    height = height_tree(p1);
    printf("%d", height);
    finish(p1);
    return (0);
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
