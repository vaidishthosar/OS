#include <stdio.h>
#include <stdlib.h>

void FCFS(int frameSize, int* pageReferences, int pageReferencesCount) {
    int* frames = (int*)malloc(sizeof(int) * frameSize);
    int pageFaults = 0;

    // Initialize frames with -1 (indicating empty frames)
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }

    // Process page references
    for (int i = 0; i < pageReferencesCount; i++) {
        int pageReference = pageReferences[i];
        int hit = 0;

        // Check if the page is already in frames
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pageReference) {
                hit = 1;
                break;
            }
        }

        // If it's not in frames, perform page replacement
        if (!hit) {
            int replacedPageIndex = pageFaults % frameSize; // Index for the page to be replaced
            frames[replacedPageIndex] = pageReference;
            pageFaults++;
        }

        // Display the frames after each reference
        printf("%d: ", pageReference);
        for (int j = 0; j < frameSize; j++) {
            printf("%d ", frames[j]);
        }

        if (hit) {
            printf("Hit\n");
        } else {
            printf("Miss\n");
        }
    }

    // Display the total number of page faults
    printf("Page faults: %d\n", pageFaults);

    free(frames);
}

void LRU(int frameSize, int* pageReferences, int pageReferencesCount) {
    int* frames = (int*)malloc(sizeof(int) * frameSize);
    int* recentlyUsed = (int*)malloc(sizeof(int) * frameSize);
    int pageFaults = 0;

    // Initialize frames with -1 (indicating empty frames)
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        recentlyUsed[i] = 0; // Initialize recently used array to 0
    }

    // Process page references
    for (int i = 0; i < pageReferencesCount; i++) {
        int pageReference = pageReferences[i];
        int hit = 0;

        // Check if the page is already in frames
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pageReference) {
                hit = 1;
                recentlyUsed[j] = i + 1; // Update the recently used time
                break;
            }
        }

        // If it's not in frames, perform page replacement
        if (!hit) {
            int lruIndex = 0;
            // Find the least recently used page in frames
            for (int j = 1; j < frameSize; j++) {
                if (recentlyUsed[j] < recentlyUsed[lruIndex]) {
                    lruIndex = j;
                }
            }

            frames[lruIndex] = pageReference; // Replace the least recently used page
            recentlyUsed[lruIndex] = i + 1; // Update the recently used time
            pageFaults++;
        }

        // Display the frames after each reference
        printf("%d: ", pageReference);
        for (int j = 0; j < frameSize; j++) {
            printf("%d ", frames[j]);
        }

        if (hit) {
            printf("Hit\n");
        } else {
            printf("Miss\n");
        }
    }

    // Display the total number of page faults
    printf("Page faults: %d\n", pageFaults);

    free(frames);
    free(recentlyUsed);
}

int findOptimalIndex(int* pageReferences, int pageReferencesCount, int* frames, int frameSize, int startIndex) {
    int index = -1;
    int farthest = startIndex;

    for (int i = 0; i < frameSize; i++) {
        int j;
        for (j = startIndex; j < pageReferencesCount; j++) {
            if (frames[i] == pageReferences[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == pageReferencesCount)
            return i;
    }
    return (index == -1) ? 0 : index;
}

void Optimal(int frameSize, int* pageReferences, int pageReferencesCount) {
    int* frames = (int*)malloc(sizeof(int) * frameSize);
    int pageFaults = 0;

    // Initialize frames with -1 (indicating empty frames)
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }

    // Process page references
    for (int i = 0; i < pageReferencesCount; i++) {
        int pageReference = pageReferences[i];
        int hit = 0;

        // Check if the page is already in frames
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pageReference) {
                hit = 1;
                break;
            }
        }

        // If it's not in frames, perform page replacement
        if (!hit) {
            int replacedPageIndex = findOptimalIndex(pageReferences, pageReferencesCount, frames, frameSize, i + 1);
            frames[replacedPageIndex] = pageReference;
            pageFaults++;
        }

        // Display the frames after each reference
        printf("%d: ", pageReference);
        for (int j = 0; j < frameSize; j++) {
            printf("%d ", frames[j]);
        }

        if (hit) {
            printf("Hit\n");
        } else {
            printf("Miss\n");
        }
    }

    // Display the total number of page faults
    printf("Page faults: %d\n", pageFaults);

    free(frames);
}

int main() {
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
