#include<stdio.h>
#include<stdlib.h>

void FCFS(int frameSize , int* pageReferences , int pageReferencesCount){

    int* frames = (int*)malloc(sizeof(int)*frameSize);
    int pageFaults = 0;

    for(int i = 0 ; i < frameSize ; i++){
        frames[i] = -1;
    }

    for(int i = 0 ; i < pageReferencesCount ; i++){

        int hit = 0;
        int tempPage = pageReferences[i];

        for(int j = 0 ; j < frameSize ; j++){
            if(frames[j] == tempPage){
                hit = 1;
            }
        }

        if(hit == 0){
            int faultFrame = pageFaults%frameSize;
            frames[faultFrame] = tempPage;
            pageFaults++;
        }

        printf("%d : ",tempPage);
        for(int j = 0 ; j < frameSize ; j++){
            printf("%d ",frames[j]);
        }

        if(hit == 0){
            printf("Hit\n");
        }else{
            printf("Miss\n");
        }
    }

    printf("Page faults : %d",pageFaults);
    free(frames);

}

int main(){
    int frameSize, pageReferencesCount;

    // Read frame size from the user
    printf("Enter the frame size: ");
    scanf("%d", &frameSize);

    // Read the number of page references from the user
    printf("Enter the number of page references: ");
    scanf("%d", &pageReferencesCount);

    // Dynamically allocate memory for pageReferences array
    int* pageReferences = (int*)malloc(sizeof(int) * pageReferencesCount);

    // Read page references from the user
    for (int i = 0; i < pageReferencesCount; i++) {
        printf("Enter page reference %d: ", i + 1);
        scanf("%d", &pageReferences[i]);
    }

    // Call the FCFS page replacement algorithm
    FCFS(frameSize, pageReferences, pageReferencesCount);

    // Free dynamically allocated memory
    free(pageReferences);

    return 0;
}