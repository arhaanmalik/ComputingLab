#include<stdio.h>
void merge(int arr[],int low,int mid,int high)
{
    int size=high-low+1;
    int i=low,j=mid+1;
    int arr2[size];
    int k=0;
    while(i <= mid && j<= high)
    {
        if(arr[i] <= arr[j])
            arr2[k++]=arr[i++];
        else
            arr2[k++]=arr[j++];
    }
    while(i <= mid)
        arr2[k++]=arr[i++];
    while(j <= high)
        arr2[k++]=arr[j++];
    for(i=low;i<=high;i++)
        arr[i]=arr2[i-low];
}
void merge_sort(int arr[],int low,int high)
{
    if(low < high)
    {
    int mid=(low+high)/2;
    merge_sort(arr,low,mid);
    merge_sort(arr,mid+1,high);
    merge(arr,low,mid,high);
    }
}
int main()
{
    int n,i;
    printf("Enter size of array");
    scanf("%d",&n);
    int arr[n];
    printf("Enter elemnts of array");
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);
    merge_sort(arr,0,n-1);
    printf("After sorting :");
    for(i=0;i<n;i++)
        printf("%d ",arr[i]);
    int product=1,prod1=1,prod2=1,prod3=1,max=1;;
    printf("Maximum product is :");
    if(n >= 5)
    {
        prod1=arr[n-1]*arr[n-2]*arr[n-3]*arr[n-4]*arr[n-5];
        prod2=arr[n-1]*arr[n-2]*arr[n-3]*arr[0]*arr[1];
        prod3=arr[n-1]*arr[0]*arr[1]*arr[2]*arr[3];
    }
    if(prod1 >= prod2)
    {
        if(prod1 >= prod3)
            max=prod1;
        else
            max=prod3;
    }
    else
    {
        if(prod2 >= prod3)
            max=prod2;
        else
            max=prod3;
    }
    printf("max product is %d",max);
}