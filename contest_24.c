//2025_プログラミングコンテスト_本選_酸性
//左上から横ペアを詰めていく
//下2段目から縦のペアで左に詰めていく
//最後に特殊な動きを行いすべてのペアを揃える
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 256
#define Shikou 10

struct data make_data(void);
void show(struct data s);                                           //配列を表示
struct data lright_spin(struct data s, int x, int y, int size);     //little_right_spin 範囲を指定した後に回転
struct data mitibiki(struct data s, int sintyoku);                   //値を導く
void search(struct data s, int *x1, int *y1, int *x2, int *y2);     //ペアの値の座標を探す関数
void mokuhyou(int *x, int *y, int count, int n);                    //揃えたい値を定める関数
void base_point(int *x1, int *y1, int *x2, int *y2, int n);         //基点を打つ関数
//void arrange(struct data s, int a[526][]);                        //揃える関数
void way(struct data s, int x1, int y1, int x2, int y2);            //値を揃えるための道筋を求める関数
int jadge(struct data s);                                           //ペアの数を数える

int n;

struct data{
    int str[100][100];
};

int main(void)
{
    int i; //仮引数
    int j; //仮引数
    int end = 0; //最終的なペア
    int x; //ペアを探すための引数 x
    int y; //ペアを探すための引数 y
    int pear; //ペアの数値
    int size;
    int count = 0;
    int sintyoku = 0;
    struct data s;
    struct data t;

    //初期化

    //入力
    printf("size:");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            scanf("%d", &s.str[i][j]);
        }
    }

    //操作
    end = n * n / 2;
    i = 0;

    sintyoku = 0;
    while(count < end){
        printf("sintyoku:%d\n", sintyoku);
        s = mitibiki(s, sintyoku);
        show(s);
        count = jadge(s);
        sintyoku++;
    }
    
    
    //最終表示
    for(i = 0; i < n + 1; i++){
        for(j = 0; j < n + 1; j++){
            printf("%2d", s.str[i][j]);
        }
        printf("\n");
    }
    printf("count:%d\n", count);

    return (0);
}

struct data mitibiki(struct data s, int sintyoku)
{
    int i;
    int j;
    int a;
    int x_left = 0;
    int y_left = 0;
    int sidex;
    int sidey;
    int x_right;
    int y_right;
    int max;
    int max_pear;
    int count = jadge(s);
    int sousa[576][3];
    int zahyou[576][2];

    for(i = 0; i < 576; i++){
        sousa[i][0] = 0;
        sousa[i][1] = 0;
        sousa[i][2] = 1;
        zahyou[i][0] = 0; 
        zahyou[i][1] = 0; 
    }

//    printf("side:");
//    scanf("%d %d", &sidex, &sidey);
    max_pear = n * n / 2;
    sidex = sintyoku * 2 % n;
    sidey = (int)(sintyoku / (n / 2)); 
    if(n - sidey <= 2){
        
        sidex = sintyoku % n;
        sidey = n - 1;
    }
    
    search(s, &sidex, &sidey, &x_right, &y_right);
    printf("side:%d %d\n", sidex, sidey);
    
    printf("right:%d %d\n", x_right, y_right);
    zahyou[0][0] = x_right;
    zahyou[0][1] = y_right;

    
    if((max_pear - sintyoku == 2) && (s.str[n - 2][n - 2] == s.str[n - 1][n - 1])){
        printf("3.Hi\n");
        sousa[0][0] = 0;
        sousa[0][1] = 0;
        sousa[0][2] = 1;

        i = 0;
        i++;
        sousa[i][0] = n - 2;
        sousa[i][1] = n - 3;
        sousa[i][2] = 2;
        i++;
        sousa[i][0] = n - 4;
        sousa[i][1] = n - 3;
        sousa[i][2] = 3;

    }
    else if((n - sidey <= 2) &&(max_pear - n <= sintyoku)){
        printf("2.Hi\n");
        
        i = 0;
        x_left = sidex + 1;
        y_left = n - 1;
        sousa[0][0] = 0;
        sousa[0][1] = 0;
        sousa[0][2] = 1;
        
        while((zahyou[i][0] != x_left || zahyou[i][1] != y_left) && i < Shikou){
            i++;

            if(zahyou[i - 1][1] == y_left){
                printf("6-1.Hello\n");
                if(zahyou[i - 1][0] == x_left + 1){
                    sousa[i][0] = x_left;
                    sousa[i][1] = y_left - 1;
                    sousa[i][2] = 2;
                    zahyou[i][0] = x_left;
                    zahyou[i][1] = y_left;
                }
                else{
                    sousa[i][0] = zahyou[i - 1][0] - 1;
                    sousa[i][1] = zahyou[i - 1][1] - 1;
                    sousa[i][2] = 2;
                    zahyou[i][0] = zahyou[i - 1][0] - 1;
                    zahyou[i][1] = zahyou[i - 1][1]; 
                }
            }
            else{
                printf("6-2.Hello\n");
                if(zahyou[i - 1][0] == x_left){
                    sousa[i][0] = zahyou[i - 1][0];
                    sousa[i][1] = zahyou[i - 1][1];
                    sousa[i][2] = 2;
                    zahyou[i][0] = zahyou[i - 1][0] + 1;
                    zahyou[i][1] = zahyou[i - 1][1];
                }
                else{
                    sousa[i][0] = zahyou[i - 1][0] - 1;
                    sousa[i][1] = zahyou[i - 1][1];
                    sousa[i][2] = 2;
                    zahyou[i][0] = zahyou[i - 1][0];
                    zahyou[i][1] = zahyou[i - 1][1] + 1;
                }
            }
        
        }
        i++;
        sousa[i][0] = sidex;
        sousa[i][1] = y_left - 1;
        sousa[i][2] = 2;
    }
    else if(n - sidex <= 2){
        printf("1.Hi\n");
        i = 0;

        x_left = sidex;
        y_left = sidey + 1;

        while((zahyou[i][0] != x_left || zahyou[i][1] != y_left) && i < Shikou){
            i++;

            if(zahyou[i - 1][1] < y_left){
                printf("0.Hello\n");
                break;
            }

            if(zahyou[i - 1][0] == x_left){ //x座標が一致している場合
                a = zahyou[i - 1][1] - y_left + 1; //目標と揃えたい座標のy座標の距離
                printf("a:%d\n", a);
            
                if(zahyou[i - 1][0] + a <= n){ //距離が最大範囲内だった場合
                    printf("1.Hello\n");
                    sousa[i][0] = x_left;
                    sousa[i][1] = y_left;
                    sousa[i][2] = a;
                    zahyou[i][0] = x_left;
                    zahyou[i][1] = y_left;
                }
                else{ //距離が最大範囲外だった場合
                    printf("2.Hello\n");
                    max = n - zahyou[i - 1][0];
                    sousa[i][0] = x_left;
                    sousa[i][1] = zahyou[i - 1][1] - max + 1;
                    sousa[i][2] = max;
                    zahyou[i][0] = x_left;
                    zahyou[i][1] = zahyou[i - 1][1] - max + 1;
                }
            }
            else if(zahyou[i - 1][0] > x_left){ //目標のx座標が揃えたい位置より右の場合　とりあえずx座標を揃えられるよう誘導
                a = zahyou[i - 1][0] - x_left + 1; //目標と揃えたい座標のx座標の距離
                printf("a:%d\n", a);
                printf("3.Hello\n");
            
                if(zahyou[i - 1][1] == y_left){
                    max = n - y_left;
                    if(a <= max){
                        printf("3-1-1.Hello\n");
                        sousa[i][0] = x_left;
                        sousa[i][1] = y_left;
                        sousa[i][2] = a;
                        zahyou[i][0] = zahyou[i - 1][0];
                        zahyou[i][1] = zahyou[i - 1][1] + zahyou[i - 1][0] - x_left; 
                    }
                    else{
                        printf("3-1-2.Hello\n");
                        sousa[i][0] = zahyou[i - 1][0] - max + 1;
                        sousa[i][1] = y_left;
                        sousa[i][2] = max;
                        zahyou[i][0] = zahyou[i - 1][0]; 
                        zahyou[i][1] = zahyou[i - 1][1] + max - 1;
                    }
                }
                else{
                    max = zahyou[i - 1][1] - y_left;
                    if(x_left + y_left < zahyou[i - 1][0]){ //条件が間違っている?　処理の都合上、正解を導いてしまうことがある
                        printf("3-2-1.Hello\n");
                        sousa[i][0] = zahyou[i - 1][0] - max;
                        sousa[i][1] = zahyou[i - 1][1] - max;
                        sousa[i][2] = max + 1;
                        zahyou[i][0] = zahyou[i - 1][0] - max;
                        zahyou[i][1] = zahyou[i - 1][1];
                    }
                    else{
                        printf("3-2-2.Hello\n");
                        sousa[i][0] = x_left;
                        sousa[i][1] = zahyou[i - 1][1] - (zahyou[i - 1][0] - x_left);
                        sousa[i][2] = zahyou[i - 1][0] - x_left + 1;
                        zahyou[i][0] = x_left;
                        zahyou[i][1] = zahyou[i - 1][1];
                    }

                }
            }
            else if(zahyou[i - 1][0] < x_left){ //目標のx座標が揃えたい位置より左の場合　とりあえずx座標を揃えられるよう誘導
                a = x_left - zahyou[i - 1][0] + 1; //目標と揃えたい座標のx座標の距離
                printf("a:%d\n", a);
                printf("4.Hello\n");
            
                if(n - zahyou[i - 1][0] < zahyou[i - 1][1] - y_left){
                    max = n - zahyou[i - 1][0];
                }
                else{
                    max = zahyou[i - 1][1] - y_left;
                }
                if(a <= n - zahyou[i - 1][1]){
                    printf("4-1.Hello\n");
                    sousa[i][0] = zahyou[i - 1][0];
                    sousa[i][1] = zahyou[i - 1][1];
                    sousa[i][2] = a;
                    zahyou[i][0] = x_left;
                    zahyou[i][1] = zahyou[i - 1][1];
                }
                else{
                    printf("4-2.Hello\n");
                    sousa[i][0] = zahyou[i - 1][0];
                    sousa[i][1] = zahyou[i - 1][1] - max + 1;
                    sousa[i][2] = max;
                    zahyou[i][0] = zahyou[i - 1][0];
                    zahyou[i][1] = zahyou[i - 1][1] - max + 1;
                }
            
            }        

        }
        
        printf("--Hello--\n");
        i++;
        sousa[i][0] = x_left;
        sousa[i][1] = y_left - 1;
        sousa[i][2] = 2;
        
    }
    else{
        printf("0.Hi\n");
        i = 0;

        x_left = sidex + 1;
        y_left = sidey;

        printf("left:%d %d\n", x_left, y_left);

        while((zahyou[i][0] != x_left || zahyou[i][1] != y_left) && i < Shikou){
            i++;

            if(zahyou[i - 1][1] < y_left){
                printf("0.Hello\n");
                break;
            }

            if(zahyou[i - 1][0] == x_left){ //x座標が一致している場合
                a = zahyou[i - 1][1] - y_left + 1; //目標と揃えたい座標のy座標の距離
                printf("a:%d\n", a);
            
                if(zahyou[i - 1][0] + a <= n){ //距離が最大範囲内だった場合
                    printf("1.Hello\n");
                    sousa[i][0] = x_left;
                    sousa[i][1] = y_left;
                    sousa[i][2] = a;
                    zahyou[i][0] = x_left;
                    zahyou[i][1] = y_left;
                }
                else{ //距離が最大範囲外だった場合
                    printf("2.Hello\n");
                    max = n - zahyou[i - 1][0];
                    sousa[i][0] = x_left;
                    sousa[i][1] = zahyou[i - 1][1] - max + 1;
                    sousa[i][2] = max;
                    zahyou[i][0] = x_left;
                    zahyou[i][1] = zahyou[i - 1][1] - max + 1;
                }
            }
            else if(zahyou[i - 1][0] > x_left){ //目標のx座標が揃えたい位置より右の場合　とりあえずx座標を揃えられるよう誘導
                a = zahyou[i - 1][0] - x_left + 1; //目標と揃えたい座標のx座標の距離
                printf("a:%d\n", a);
                printf("3.Hello\n");
            
                if(zahyou[i - 1][1] == y_left){
                    max = n - y_left;
                    if(a <= max){
                        printf("3-1-1.Hello\n");
                        sousa[i][0] = x_left;
                        sousa[i][1] = y_left;
                        sousa[i][2] = a;
                        zahyou[i][0] = zahyou[i - 1][0];
                        zahyou[i][1] = zahyou[i - 1][1] + zahyou[i - 1][0] - x_left; 
                    }
                    else{
                        printf("3-1-2.Hello\n");
                        sousa[i][0] = zahyou[i - 1][0] - max + 1;
                        sousa[i][1] = y_left;
                        sousa[i][2] = max;
                        zahyou[i][0] = zahyou[i - 1][0]; 
                        zahyou[i][1] = zahyou[i - 1][1] + max - 1;
                    }
                }
                else{
                    max = zahyou[i - 1][1] - y_left;
                    if(x_left + y_left < zahyou[i - 1][0]){ //条件が間違っている?　処理の都合上、正解を導いてしまうことがある
                        printf("3-2-1.Hello\n");
                        sousa[i][0] = zahyou[i - 1][0] - max;
                        sousa[i][1] = zahyou[i - 1][1] - max;
                        sousa[i][2] = max + 1;
                        zahyou[i][0] = zahyou[i - 1][0] - max;
                        zahyou[i][1] = zahyou[i - 1][1];
                    }
                    else{
                        printf("3-2-2.Hello\n");
                        sousa[i][0] = x_left;
                        sousa[i][1] = zahyou[i - 1][1] - (zahyou[i - 1][0] - x_left);
                        sousa[i][2] = zahyou[i - 1][0] - x_left + 1;
                        zahyou[i][0] = x_left;
                        zahyou[i][1] = zahyou[i - 1][1];
                    }

                }
            }
            else if(zahyou[i - 1][0] < x_left){ //目標のx座標が揃えたい位置より左の場合　とりあえずx座標を揃えられるよう誘導
                a = x_left - zahyou[i - 1][0] + 1; //目標と揃えたい座標のx座標の距離
                printf("a:%d\n", a);
                printf("4.Hello\n");
            
                if(n - zahyou[i - 1][0] < zahyou[i - 1][1] - y_left){
                    max = n - zahyou[i - 1][0];
                }
                else{
                    max = zahyou[i - 1][1] - y_left;
                }
                if(a <= n - zahyou[i - 1][1]){
                    printf("4-1.Hello\n");
                    sousa[i][0] = zahyou[i - 1][0];
                    sousa[i][1] = zahyou[i - 1][1];
                    sousa[i][2] = a;
                    zahyou[i][0] = x_left;
                    zahyou[i][1] = zahyou[i - 1][1];
                }
                else{
                    printf("4-2.Hello\n");
                    sousa[i][0] = zahyou[i - 1][0];
                    sousa[i][1] = zahyou[i - 1][1] - max + 1;
                    sousa[i][2] = max;
                    zahyou[i][0] = zahyou[i - 1][0];
                    zahyou[i][1] = zahyou[i - 1][1] - max + 1;
                }
            
            }        

        }
    }

    //実行
    printf("i %d\n", i);
    j = 1;
    while(j <= i){
        printf("%d %d %d\n", sousa[j][0], sousa[j][1], sousa[j][2]);
        s = lright_spin(s, sousa[j][0], sousa[j][1], sousa[j][2]);
        j++;
    }

    return (s);
}


struct data make_data(void)
{
    struct data s;
    int n;
    int i;
    int j;

    printf("size:");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d %d:", i, j);
            scanf(" %d", &s.str[i][j]);
        }
    }
    return (s);
}

void show(struct data s){
    int i;
    int j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%2d", s.str[i][j]);
        }
        printf("\n");
    }
}

struct data lright_spin(struct data s, int x, int y, int size)
{
    struct data c;
    struct data d;
    int i;
    int j;

    n = 4;
    if(x >= n || y >= n){
        printf("can't spin\n");
        return (s);
    }

    for(i = 0; i < n + 1; i++){
        for(j = 0; j < n + 1; j++){
            d.str[i][j] = s.str[i][j];
            c.str[i][j] = s.str[i][j];
        }
    }

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            c.str[i + y][j + x] = d.str[y + size - j - 1][x + i];
        }
    }

    return(c);
}

int jadge(struct data s){
    int i;
    int j;
    int count = 0;

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(s.str[i][j] == s.str[i][j + 1] || s.str[i][j] == s.str[i + 1][j]){
                count++;
            }
        }
    }

    printf("\n");

    return (count);
}

void mokuhyou(int *x, int *y, int count, int n)
{
    *x = (count % (n / 2)) * 2;
    *y = count / (n / 2);
}

void search(struct data s, int *x1, int *y1, int *x2, int *y2)
{
    int i;
    int j;
    int key;
    i = *x1;
    j = *y1;
    key = s.str[*y1][*x1];
    do{
        i++;
        if(i >= n){
            i = 0;
            j++;
        }
        if(s.str[j][i] == key){
            break;
        }
    }while(s.str[j][i] != key);
    *x2 = i;
    *y2 = j;
    
}


