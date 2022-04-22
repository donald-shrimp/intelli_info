#include <stdio.h>
#include <stdlib.h>

#define N 256 // 1行の最大文字数(バイト数)
#define ROW 150 // 読み込むファイルのデータの行数
 
// 1列目の項目名と2列目以降のデータを格納する配列をメンバにもつ構造体
// １．パラメータの設定：データ数，クラス数，特徴空間の次元数，k-最近傍法の k の値など 
typedef struct iris {
	float iris_data[4];
    int iris_label;
} data;
 
// ２．Iris.txt のデータの入力

int main(void) {
	FILE *fp; // FILE型構造体
	char fname[] = "iris.txt";
	char line[N];
	float f1, f2, f3, f4;
    int label;
	int i = 0;
 
	data data[ROW];
 
	fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	}
 
	while(fgets(line, N, fp) != NULL) {
		sscanf(line, "%f,%f,%f,%f,%d",&f1, &f2, &f3, &f4, &label);
 	
		float tmp[] = {f1, f2, f3, f4};
		for(int j = 0; j  < 4; j++) {
			data[i].iris_data[j] = tmp[j];
		}//4つのデータを入力
		
        data[i].iris_label = label;//ラベルを入力
		
        i++;
	}
 
	fclose(fp); // ファイルを閉じる

printf("%f,%f,%f,%f,%d\n",&data[1].iris_data[1], &data[1].iris_data[1], &data[1].iris_data[1], &data[1].iris_data[1], &data[1].iris_label);
// float ymax=5.0,ymin=1.0,xmax=8.0,xmin=4.0;

}

// ３．Iris データの２つの特徴量の取りうる値の範囲を事前に求める 

// ４．３で求めた範囲内で，未知データの 2 成分をキーボード入力する 

// ５．k-最近傍法のアルゴリズムで未知データのクラス番号（0,1,2 のいずれか）を決定して，出力する 
