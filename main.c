#include <stdio.h>
#include <stdlib.h>

int  Parent(i) { return (i-1)/2; }
int  Left(i) { return 2*i+1; }
int  right(i) { return 2*i + 2;}

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
    if(Parent(i)>=0)
 {


	if(arr[i].balance>arr[Parent(i)].balance)
    {
        Item temp;
        temp=arr[Parent(i)];
        arr[Parent(i)]=arr[i];
        arr[i]=temp;

        max_heapify(arr,n,Parent(i));
    }
    else
    {
        //max_heapify(arr,n,Parent(i));
        return;
    }
 }
 else
 {
     return;
 }
}
void max_heapify2(Item *arr, int n, int i)
{

	if(arr[i].balance<arr[right(i)].balance&&right(i)<=n-1)
    {
        double temp;
        temp=arr[i].balance;
        arr[i].balance=arr[right(i)].balance;
        arr[right(i)].balance=temp;
        max_heapify2(arr,n,right(i));
        max_heapify2(arr,n,i);

    }
    if(arr[i].balance<arr[Left(i)].balance&&Left(i)<=n-1)
    {
        double temp;
        temp=arr[i].balance;
        arr[i].balance=arr[Left(i)].balance;
        arr[Left(i)].balance=temp;
        max_heapify2(arr,n,Left(i));
        max_heapify2(arr,n,i);
    }
    else
    {
        return;
    }
}
void max_heapify3(Item *arr, int n, int i)
{

    if(arr[i].balance<arr[right(i)].balance&&right(i)<=n-1)
    {
        Item temp;
        temp=arr[i];
        arr[i]=arr[right(i)];
        arr[right(i)]=temp;
        max_heapify3(arr,n,right(i));
        //max_heapify2(arr,n,i);

    }
    if(arr[i].balance<arr[Left(i)].balance&&Left(i)<=n-1)
    {
        Item temp;
        temp=arr[i];
        arr[i]=arr[Left(i)];
        arr[Left(i)]=temp;
        max_heapify3(arr,n,Left(i));
        //max_heapify2(arr,n,i);
    }
    else
    {
        return;
    }


}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
 Item extract_maximum(Item*arr,int* n)
{
	Item max= arr[0];
    Item temp=arr[0];
    arr[0]=arr[(*n)-1];
    arr[(*n)-1]=temp;
    (*n)--;
    max_heapify3(arr,*n,0);
    //max_heapify(arr,*n,(*n)-1);
    return max;

}
int sortSimilar(int i,Item* current,Item* lag,int arraySize, Item queue[arraySize])
{
    double balance=(*lag).balance;
            Item similarBalanceArray[arraySize];
            similarBalanceArray[0]=*lag;
            printf("Similar=%10s    %.1lf   %2d\n",similarBalanceArray[0].cName,similarBalanceArray[0].balance,similarBalanceArray[0].order);
            int j=1;
            int similarBalanceArrayRealSize=1;
            while((*current).balance==balance)
            {
               similarBalanceArray[j]=*current;
                printf("Similar=%10s    %.1lf   %2d\n",similarBalanceArray[j].cName,similarBalanceArray[j].balance,similarBalanceArray[j].order);

               i++;
               j++;
               similarBalanceArrayRealSize++;
               *lag=*current;
               *current=queue[i];
            }
            int k,l;
            for(k=0;k<similarBalanceArrayRealSize;k++)
            {
                for(l=0;l<similarBalanceArrayRealSize-k;l++)
                {
                    if(similarBalanceArray[l].order>similarBalanceArray[l+1].order)
                    {
                        Item temp =similarBalanceArray[l];
                        similarBalanceArray[l]=similarBalanceArray[l+1];
                        similarBalanceArray[l+1]=temp;
                    }
                }
            }
            for(k=0;k<similarBalanceArrayRealSize;k++)
            {
                printf("Sorted Similar=%10s    %.1lf   %5d\n",similarBalanceArray[k].cName,similarBalanceArray[k].balance,similarBalanceArray[k].order);
            }
            for(k=0;k<similarBalanceArrayRealSize;k++)
            {
                queue[i-similarBalanceArrayRealSize+k]=similarBalanceArray[k];
                printf("from similarArray to Queue=%10s    %.1lf   \n",similarBalanceArray[k].cName,similarBalanceArray[k].balance);
            }
            return similarBalanceArrayRealSize;
}
Item* construct_PQ(Item*arr,int n)
{

    int arraySize=n;
    int i,j;
    Item queue[arraySize];
    for(i=0;i<arraySize;i++)
    {
        queue[i]=extract_maximum(arr,&n);
        printf("%10s    %.1lf   %2d extracted to queue arraySize=%d n=%d\n",queue[i].cName,queue[i].balance,queue[i].order,arraySize,n);
    }
    for(i=0;i<arraySize;i++)
    {
        Item current;
        Item lag=current;
        current=queue[i];
        if (lag.balance==current.balance)
        {
            i=i+sortSimilar(i,&current,&lag,arraySize,queue);
           /* double balance=lag.balance;
            Item similarBalanceArray[arraySize];
            similarBalanceArray[0]=lag;
            printf("Similar=%10s    %.1lf   \n",similarBalanceArray[0].cName,similarBalanceArray[0].balance);
            int j=1;
            int similarBalanceArrayRealSize=1;
            while(current.balance==balance)
            {
               similarBalanceArray[j]=current;
                printf("Similar=%10s    %.1lf   \n",similarBalanceArray[j].cName,similarBalanceArray[j].balance);

               i++;
               j++;
               similarBalanceArrayRealSize++;
               lag=current;
               current=queue[i];
            }
            int k,l;
            for(k=0;k<similarBalanceArrayRealSize;k++)
            {
                for(l=0;l<similarBalanceArrayRealSize-k;l++)
                {
                    if(similarBalanceArray[l].order>similarBalanceArray[l+1].order)
                    {
                        Item temp =similarBalanceArray[l];
                        similarBalanceArray[l]=similarBalanceArray[l+1];
                        similarBalanceArray[l+1]=temp;
                    }
                }
            }
            for(k=0;k<similarBalanceArrayRealSize;k++)
            {
                queue[i-similarBalanceArrayRealSize+k]=similarBalanceArray[k];
                printf("from similarArray to Queue=%10s    %.1lf   \n",similarBalanceArray[k].cName,similarBalanceArray[k].balance);
            }*/
            //similarBalanceArrayRealSize=0;

        }

    }
    /*printf("Queue construct fn\n");
    for(i=0;i<arraySize;i++)
    {
        printf("%lf %d\n",queue[i].balance,queue[i].order);
    }*/
    printCustomersbyPriority(queue,arraySize);
    return queue;
}
/*
 * delete the item with max priority and then return it.
 */

/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
	FILE* f=fopen("abc.txt","r");
	if(f!=NULL)
    {int i=0;
        while(!feof(f))
        {
            arr[i].cName=malloc(sizeof(char)*30);
            fscanf(f,"%s %lf",arr[i].cName,&arr[i].balance);
            arr[i].order=i;
            printf("%s %lf %d\n",arr[i].cName,arr[i].balance,arr[i].order);
            max_heapify(arr,5,i);//5 is a dummy argument
            fscanf(f,"\n");
            i++;
        }
        fclose(f);
        return i;
    }
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{
    int i;
    int arraySize=n;
    printf("Print at last fn\n");
    for(i=0;i<arraySize;i++)
    {
        //printf("bal:%lf\n",extract_maximum(arr,&n).balance);
        printf("Element %2d",i);
        printf("%20s    %.1lf   %d\n",arr[i].cName,arr[i].balance,arr[i].order);

    }

}
/*
 *
 */
/*int main(int argc, char**argv) {

	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}*/

int main()
{
    int i;

    Item *customers=(Item*)malloc(sizeof(Item)*100);
    //Item customers[100];
    int arrLength=fillArrayFromFile("",customers);

    customers=construct_PQ(customers,arrLength);
    //printCustomersbyPriority(customers,arrLength);
    /*for(i=0;i<arrLength;i++)
    {

        printf("%lf",customers[i].balance);
        if(Left(i)<arrLength)
        printf("   %lf   ",customers[Left(i)].balance);
        else
            printf("         ");
        if(right(i)<arrLength)
        printf("   %lf   ",customers[right(i)].balance);
        else
            printf("         ");
        printf("\n");

    }*/

    return 0;

}
