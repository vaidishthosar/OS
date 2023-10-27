#include<stdio.h>

int main(){

    int n = 5;
    int m = 3;
    int index = 0;

    int allocated[5][3] = {{0,1,0},
                       {2,0,0},
                       {3,0,2},
                       {2,1,1},
                       {0,0,2}};

    int max[5][3] = { { 7, 5, 3 }, 
                      { 3, 2, 2 }, 
                      { 9, 0, 2 }, 
                      { 2, 2, 2 }, 
                      { 4, 3, 3 } };

    int available[3] = {3 , 3 , 2};

    int flags[n];
    int ans[n];
    int need[n][m];

    for(int i = 0 ; i < n ; i++){
        flags[i] = 0;
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    for(int k = 0 ; k < n ; k++){
        for(int i = 0 ; i < n ; i++){
            if(flags[i] == 0){
                int flag = 0;
                for(int j = 0 ; j < m ; j++){
                    if(need[i][j]>=available[i]){
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0){
                    ans[index] = i;
                    index++;
                    for(int j = 0 ; j < m ; j++){
                        available[j] += allocated[i][j];
                        flags[i] = 1;
                    }
                    
                }
            }
        }
    }

    

    for(int i = 0 ; i < n ; i++){
        if(flags[i] == 0){
            printf("The given sequence is not safe: ");
            return 0;
        }
    }

    printf("Following is the SAFE Sequence :");
	for (int i = 0; i < n ; i++)
		printf(" P %d ->",ans[i]) ;

    
}