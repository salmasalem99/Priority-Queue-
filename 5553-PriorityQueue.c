#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
 char* cName;
 double balance;
 int order;
}Item;
/*
 * Heapify index i in array of Items with size n
 */
void max_heapify(Item *arr, int n, int i)
{
	int child1 = 2*i;
	int child2 =(2*i)+1;
	int temp;
	int flag = 0;
	double tempBalance;
	char* tempName;
	int tempOrder;
	if(child1<=n && child2<=n)
    {
        flag =1;
        if(arr[child1].balance>arr[child2].balance ||((arr[child1].balance==arr[child2].balance)&& (arr[child1].order < arr[child2].order)))
            temp = child1;
        else if(arr[child2].balance>arr[child1].balance ||((arr[child1].balance==arr[child2].balance)&& (arr[child2].order < arr[child1].order)))
            temp = child2;
    }
    else if(child1<=n && !(child2<=n))
    {
        flag = 1;
        temp = child1;
    }
    else if(child2<=n && !(child1<=n))
    {
        flag = 1;
        temp = child2;
    }
    else
        flag = 0;
    if(flag)
    {
        tempName = (char*) malloc(sizeof(char)*10);
        strcpy(tempName,arr[i].cName);
        tempBalance=arr[i].balance;
        tempOrder=arr[i].order;
        if(arr[i].balance<arr[temp].balance || ((arr[i].balance==arr[temp].balance) && (arr[temp].order<arr[i].order)))
        {
            //percolating
            arr[i].balance=arr[temp].balance;
            strcpy(arr[i].cName,arr[temp].cName);
            arr[i].order=arr[temp].order;

            arr[temp].balance=tempBalance;
            strcpy(arr[temp].cName,tempName);
            arr[temp].order=tempOrder;
            max_heapify(arr,n,temp);
        }
    }
}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{
	for(int i=n/2;i>=1;i--)
    {
        max_heapify(arr,n,i);
    }

}
/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum(Item*arr,int n)
{
	Item temporaryItem = arr[1];
	arr[1]=arr[n];
	n--;
	max_heapify(arr,n,1);
	return temporaryItem;
}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
    FILE*f = fopen(fname,"r");
    int i=1;
    if(f!=NULL)
    {
        while(!feof(f))
        {
            arr[i].order=i;
            arr[i].cName=(char*)malloc(sizeof(char)*10);
            fscanf(f,"%s%lf\n",arr[i].cName,&arr[i].balance);
            i++;
        }
    }
    i--;
    return i;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{
    int border=n;
	for(int i=1;i<=border;i++)
    {
        Item printed=extract_maximum(arr,n);
        printf("%s\t\t%lf\t\t%d\n",printed.cName,printed.balance,printed.order);
        n--;
    }
}
/*
 *
 */
int main(int argc, char**argv) {

	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}
