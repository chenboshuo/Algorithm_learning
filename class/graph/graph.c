#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int **init(int node_size){
  int **matrix = (int**)malloc(sizeof(int*)*node_size);
  for (size_t i = 0; i < node_size; ++i){
    matrix[i] = (int*)malloc(sizeof(int)*node_size);
    for (size_t j = 0; j < node_size; ++j){
      matrix[i][j] = INT_MAX;
    }
  }
  return matrix;
}

void input_to_matrix(char* filename, int**matrix, int node_size){
  FILE* a =freopen(filename,"r",stdin); // TODO 无法读取文件
  printf("%d\n",a);
  // freopen(const char *_FileName, const char *_Mode, FILE *_Stream)
  int i,j, weight;

  // debug
  // int count=20;
  // printf("done");


  while(scanf("%d,%d,%d",&i,&j,&weight) != EOF){
    matrix[i-1][j-1] = weight;
    printf("%d\n", matrix[i-1][j-1]);
  }
  printf("%d\n", matrix[10][13] == INT_MAX);

  // for (size_t i = 0; i < node_size; ++i){
  //   for(size_t j = 0; j < node_size; ++j){
  //     if(matrix[i][j] != INT_MAX) {
  //       printf("%d ", matrix[i][j]);
  //     }else{
  //       printf("_ ");
  //     }
  //   }
  //   printf("\n");
  // }

  fclose(stdin);
}

int main(int argc, char const *argv[]) {
  int** a = init(50);
  input_to_matrix("distance.csv", a, 50);


  return 0;
}
