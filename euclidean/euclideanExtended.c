#include<stdio.h>
typedef struct{
    int d;
    int x;
    int y;
} Result;
Result Euclidean(int a,int b);
int main(){
    int a=98,b=77;
    Result r=Euclidean(a,b);
     printf("gcd(%d, %d) = %d\n", a, b, r.d);
    printf("%d(%d) + %d(%d) = %d\n", a, r.x, b, r.y, r.d);

}
Result Euclidean(int a,int b){
    int values[4]={1,0,0,1};
    int q=0,r=0;
    while(b!=0){
        q=a/b;
        r=a%b;
        int tempx=values[0]-q*values[1];
        int tempy=values[2]-q*values[3];

        a=b;
        b=r;
        values[0]=values[1];
        values[1]=tempx;
        values[2]=values[3];
        values[3]=tempy;
    }
    Result res ={a,values[0],values[2]};
    return res;
}