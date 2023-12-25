#include "iostream"
using namespace std;

struct Page{
    int value;
    int k;
};

int main(){
    int n;
    cout<<"Enter number of requests.";
    cin>>n;

    int hit=0,pagefault=0;


    cout<<"Enter the requests.";

    struct Page A[n];
    for(int i=0;i<n;i++){
        cin>>A[i].value;
        A[i].k=0;
    }

    struct Page F[4];
    for(int i=0;i<4;i++){
        F[i].k=-1;
        F[i].value=-1;
    }

    for(int i=0;i<n;i++){
        int pagefound=0;
        for(int j=0;j<4;j++){
            if(A[i].value==F[j].value){
                pagefound=1;
                hit++;
                F[j].k=i;
                break;
            }
        }

        if(!pagefound){
            pagefault++;

            int minindex=0;
            for(int k=0;k<n;k++){
                if(F[k].k < F[minindex].k){
                    minindex=k;
                }
            }

            F[minindex].value=A[i].value;
            F[minindex].k=i;


        }

        cout<<"Updated Frames :\n";
        for(int j=0;j<4;j++){
            cout<<"Page "<<j+1<<"   Value "<<F[j].value<<"  K "<<F[j].k<<endl;
        }
        cout<<endl;
    }

    cout<<"Number of hits :"<<hit<<endl;
    cout<<"Number of pagefaults :"<<pagefault<<endl;


    return 0;
}