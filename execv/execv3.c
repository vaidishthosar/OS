#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

void bsearch(int arr[] , int key , int low , int high){
    if(low<=high){
        int mid = (low+high)/2;
        if(key == arr[mid]){
            printf("Element found");
        }else if(key<arr[mid]){
            bsearch(arr,key,low,mid-1);
        }else if(key>arr[mid]){
            bsearch(arr,key,mid+1,high);
        }
    }else{
        printf("Element not found");
    }
}

void main(int argc , char*argv[]){
    int arr[argc-1];
    int loe,high,key;

    for(int i = 1 ; i < argc ; i++){
        arr[i-1] = atoi(argv[i]);
    }

    low = 0;
    high = argc-1;

    printf("Enter element to search :");
    scanf("%d",&key);

    bsearch(arr,key,low,high);

    return 0;
}