int size=0,numedges=0;;
struct edge{
	int start;
	int end;
	int weight;
	int tested;
	int selected;
}edge; 

void swap(struct edge *a, struct edge *b){ // swap elements of pointer
	struct edge temp;
	temp = *b;
	*b=*a;
	*a=temp;
}

int struct_cmp_by_weight(const void *a, const void *b) 
{ 
    struct edge *ia = (struct edge *)a;
    struct edge *ib = (struct edge *)b;
    return (int)(100.f*ia->weight - 100.f*ib->weight);
	/* float comparison: returns negative if b > a 
	and positive if a > b. We multiplied result by 100.0
	to preserve decimal fraction */ 
 
} 

int partationIndex(int number, struct edge p[number], int start,int end){
	
	int pivotIndex =start+ rand()%(end - start + 1); // generate Random Index between start and end
	int pIndex = start-1; 
	int pivot = p[pivotIndex].weight; //value of pivot at pivotIndex
	swap(&p[pivotIndex], &p[end]);  //swap pivot to end
	
	int i;
	for ( i = start; i < end ; ++i) 
	{
		if(p[i].weight<pivot){ // if value is less than pivot value than swap 
			pIndex++;
			swap(&p[i],&p[pIndex]);
			
		}
	}
	swap(&p[pIndex+1],&p[end]);
	return pIndex+1;
}

void quickSort(int number, struct edge link[number],int start, int end){
	int i;
	

	if(start<end){
		
		int pIndex = partationIndex(number,link,start,end); // getting an Index
		quickSort(number,link,start,pIndex-1); // recursion call to qucik sort function for start to Index-1 element
		quickSort(number,link,pIndex+1,end);  // recursion call to qucik sort function for Index+1 to end element
		
	}
}
