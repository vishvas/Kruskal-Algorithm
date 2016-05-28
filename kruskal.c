#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "quicksort.h"


void printMatrix(int coloumn, int (*ptr_arr)[coloumn]){
  int i,j;
  for (i = 0; i < coloumn; ++i)
  {
    for ( j = 0; j < coloumn; ++j)
      {
        if(ptr_arr[i][j]>=999){
        printf("%7s","INF");
        }else{
        printf("%7d",ptr_arr[i][j]);
        }
        
      }
      printf("\n");
  }
  
}

int height(int x, int * array){
  int height=0,i=x,parent;
  while(x!=*(array+i)){
    i=*(array+i);
    height++;
  }
  return height;
}
void union3(int x, int y, int *array){
  int x_height=height(x,array);
  int y_height=height(y,array);
  
  if(x_height==y_height){
    *(array+y)=x;
  }else if(x_height>y_height){
    *(array+y)=x;
  }else{
    *(array+x)=y;
  }

}
int find3(int find,int *array){
  //printf("Inside Find3 with value %d\n",find);
  int root=find;
  //int i=0;
  while(root!=*(array+root)){
    root=*(array+root);
    //i++;
  }
  int node=find;
  int j=0,parent;
  while(node!=root){
    parent=*(array+node);
    *(array+node)=root;
    node=parent;
  }

  return root;
}

void krushkal(int coloumn,int (*ptr_arr)[coloumn]){
    
    printMatrix(coloumn,ptr_arr);
    int i,j,k=0,numEdges=0;
    
    for ( i = 0; i < coloumn; ++i)
    {
      for ( j = 0; j < i; ++j)
      {
          if(ptr_arr[i][j]!=999){
              numEdges++;
          }
      }
    }
    printf("Number of edges are %d\n",numEdges );
    struct edge link[numEdges];
    for ( i = 0; i < coloumn; ++i)
    {
      for ( j = 0; j<i; ++j)
      {   
          if(ptr_arr[i][j]!=999){
          link[k].start=i;
          link[k].end=j;
          link[k].weight=ptr_arr[i][j];
          link[k].selected=0;
          link[k].tested=0;
          k++;
          }
      }
    }

  printf("======== Graph Edges ========\n");
  for (i = 0; i < numEdges; ++i)
  { 
      printf("Edge %d to %d - %d\n",link[i].start,link[i].end,link[i].weight);
  }

  int structs_len = sizeof(link) / sizeof(struct edge);
  printf("struct total length is %d\n",structs_len);
  //quickSort(structs_len,link,0,structs_len);
  
  
  qsort(link, structs_len, sizeof(struct edge), struct_cmp_by_weight);
  printf("===== Printing Edges After Sorting========\n");
  for (i = 0; i < structs_len; ++i)
  { 
      printf("Edge %d to %d - %d\n",link[i].start,link[i].end,link[i].weight);
  }
  int array[coloumn];
  for ( i = 0; i < coloumn; ++i) // self value to index 
  {
    array[i]=i;
  }
  
  int z;
  for (i = 0; i<structs_len; ++i)
  {   
      
      int ucomp=find3(link[i].start,array);
      int vcomp=find3(link[i].end,array);
      
      //printf("Iteration %d and Value of u-%d and v-%d \n",i,ucomp,vcomp);
      if(ucomp!=vcomp){
        link[i].selected=1;
        union3(ucomp,vcomp,array);
      }
      
  }
    
  printf("============== Selected Graph Edges=============\n");

  for (i = 0; i < numEdges; ++i)
  { 
      if(link[i].selected==1){
        printf("edge %d,%d weight=%d\n",link[i].start+1,link[i].end+1,link[i].weight);
  
      }
  }
    
}

int main(int argc, char *args[]){
	
	FILE * file_ptr = fopen(args[1], "r");
  	char * line = NULL;  	const char *s = ",";
  	size_t len = 0;
  	ssize_t read;
  	
  	int i=0,j=0,k=0;
	if (file_ptr == NULL)
    {
    	printf("\nError opening\n");
    	
    	exit(EXIT_FAILURE);
    }else{
	    while ((read=getline(&line, &len, file_ptr)) != -1){
	    	//printf("Line %s\n",line);
	     	size++;	
	    }
	}
	fclose(file_ptr); // closing the file

     int graph[size][size];

     for (i = 0; i < size; ++i) // intializing grpah with 0
      {
      	for (j = 0; j < size; ++j)
      	{
      		graph[i][j]=0;
      	}
      } 
    size_t len_two=0;
    ssize_t read_two;
    char *token=NULL; 
     i=0;
     j=0;
     FILE * file_ptr_two = fopen(args[1], "r");
     while((read_two=getline(&token, &len_two, file_ptr_two))!=-1){
     	char *value;
     	for(value=strtok(token,",");value;value=strtok(NULL,",")){
     		
     		graph[i][j]=atoi(value);
     		//printf("%d %d - %d\n",i,j,atoi(value));
     		j++;

     	}	
     	j=0;
     	i++;
     }
     krushkal(size,graph);
	   fclose(file_ptr_two);
}