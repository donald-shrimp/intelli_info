#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define N 256    // 1行の最大文字数(バイト数)
#define ROW 150  // 読み込むファイルのデータの行数
#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))
#define K 5 // kの数
#define T 10  // tの値

// １．パラメータの設定：データ数，クラス数，特徴空間の次元数，k-最近傍法の k
// の値など 1列目の項目名と2列目以降のデータを格納する配列をメンバにもつ構造体
typedef struct iris {
    float iris_data[4];
    int iris_label;
    double distance;
} data;

// ２．Iris.txt のデータの入力

int isDelimiter(char p, char delim) { return p == delim; }

int split(char* dst[], char* src, char delim) {
    int count = 0;

    for (;;) {
        while (isDelimiter(*src, delim)) {
            src++;
        }

        if (*src == '\0') break;

        dst[count++] = src;

        while (*src && !isDelimiter(*src, delim)) {
            src++;
        }

        if (*src == '\0') break;

        *src++ = '\0';
    }
    return count;
}


int compar(const void * n1, const void * n2){
	if (((data *)n1)->distance > ((data *)n2)->distance){
		return 1;
	}else if (((data *)n1)->distance < ((data *)n2)->distance){
		return -1;
	}else{
		return 0;
	}
}

int main(void) {
    FILE* fp;  // FILE型構造体
    char fname[] = "iris.txt";
    char line[N];
    char* tmp[32];
    data iris[ROW];

    fp = fopen(fname, "r");  // ファイルを開く。失敗するとNULLを返す。
    if (fp == NULL) {
        printf("%s file not open!\n", fname);
        return -1;
    }

    int unchi = 0;
    while (fgets(line, N, fp) != NULL) {
        int count;
        count = split(tmp, line, ',');
        // printf("count:%d \n",count);
        for (int i = 0; i < count; i++) {
            
            if (i == 4) {
                iris[unchi].iris_label = atoi(tmp[i]);
                // printf("%d\n\n" ,iris[unchi].iris_label);
            } else {
                iris[unchi].iris_data[i] = atof(tmp[i]);
                // printf("%lf\n" ,iris[unchi].iris_data[i]);
            }
            
        }
        unchi = unchi + 1;
    }
    fclose(fp);  // ファイルを閉じる

    // ３．Iris データの２つの特徴量の取りうる値の範囲を事前に求める
    float xmax = 5.0, xmin = 1.0, ymax = 8.0,
          ymin = 4.0;  //計算めんどいのでこれでいいや

    // ４．３で求めた範囲内で，未知データの 2 成分をキーボード入力する
    char coordinate[20];
    double x, y;
    do {
        printf(
            "x,yのように座標を入力してね "
            "xは%lf~%lfの値,yは%lf~%lfまでの値が入力できるよ！\n",
            xmin, xmax, ymin, ymax);
        scanf("%s", coordinate);
        sscanf(coordinate, "%lf,%lf", &x, &y);
        printf("x=%lf,y=%lf\n", x, y);
    } while (x < xmin || x > xmax || y < ymin || y > ymax);

    // ５．k-最近傍法のアルゴリズムで未知データのクラス番号（0,1,2のいずれか）を決定して，出力する
    
    for (int i = 0; i < ROW; i++) {
        iris[i].distance =
            (iris[i].iris_data[0] - y) * (iris[i].iris_data[0] - y) +
            (iris[i].iris_data[1] - x) * (iris[i].iris_data[1] - x);
    }

    // printf("before\n");
	// for (int i=0;i<10;i++){
	// 	printf(" iris_data;%lf    iris_label;%d    distance;%lf\n",iris[i].iris_data[0],iris[i].iris_label,iris[i].distance);
	// }

    qsort(iris, sizeof(iris)/sizeof(iris[0]), sizeof(data), compar);
    
	// printf("after\n");
	// for (int i=0;i<150;i++){
	// 	printf(" iris_data;%lf    iris_label;%d    distance;%lf\n",iris[i].iris_data[0],iris[i].iris_label,iris[i].distance);
	// }

	int most_label;
    int label_counter[3]={0,0,0};
    for (int i = 0; i < K; i++) {
        //K=1のとき、しきい値より距離が離れている場合は動作を中止する
        
        if (K==1 && iris[i].distance>T ){
            break;
        }
        
        label_counter[iris[i].iris_label]++;
        //最も多かったラベルを決めます
        
        if (i == 0 || label_counter[most_label] < label_counter[iris[i].iris_label]) {
            most_label = iris[i].iris_label;
        }
        // printf("%d\n",i);
        printf("%d番目に近いもの label:%d x:%lf    y:%lf    distance:%lf\n",i+1,iris[i].iris_label,iris[i].iris_data[1],iris[i].iris_data[0],iris[i].distance);
    }
    
    printf("たぶん%d\n", most_label);
}