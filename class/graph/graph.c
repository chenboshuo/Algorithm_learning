#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a,b)  (a)>(b) ? (b):(a)

/**
 * 初始化邻接矩阵
 * @param  node_size 节点数量
 * @return           邻接矩阵
 */
int **init(int node_size){
  int **matrix = (int**)malloc(sizeof(int*)*node_size);
  for (size_t i = 0; i < node_size; ++i){
    matrix[i] = (int*)malloc(sizeof(int)*node_size);
    for (size_t j = 0; j < node_size; ++j){
      matrix[i][j] = INT_MAX/2 - 1; // INT_MAX/2 为最大, 防止溢出
    }
  }
  return matrix;
}

/**
 * 读取矩阵
 * @param filename  文件名
 * @param matrix    邻接矩阵
 * @param node_size [description]
 */
void input_to_matrix(char* filename, int**matrix, int node_size){
  // FILE* a =freopen(filename,"r",stdin); // TODO 无法读取文件
  int i,j, weight;
  while(scanf("%d,%d,%d",&i,&j,&weight) != EOF){
    matrix[i-1][j-1] = weight;
    matrix[j-1][i-1] = weight;
  }
  fclose(stdin);
}

/**
 * floyd-waeshell 算法
 * @param matrix    矩阵
 * @param node_size 节点数量
 */
void floyd(int** matrix, int node_size){
  // 将对角线初始化为0
  for (size_t i = 0; i < node_size; ++i){
    matrix[i][i] = 0;
  }

  for (size_t k = 0; k < node_size; ++k){
    for(size_t i = 0; i < node_size; ++i){
      for(size_t j = 0; j < node_size; ++j){
        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  int** a = init(50);
  input_to_matrix("distance.csv", a, 50);
  floyd(a,50);

  for (size_t i = 0; i < 50; ++i){
    for (size_t j = 0; j < 50; ++j){
      if(a[i][j] == INT_MAX/2-1) {
        printf("_ ");
      }else{
        printf("%d ",a[i][j]);
      }
    }
    printf("\n");
  }

  return 0;
}
