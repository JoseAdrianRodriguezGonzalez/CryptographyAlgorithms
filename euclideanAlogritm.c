#include<stdio.h>
#include<stdlib.h>
int mcd(int a, int b);
int main(int argc,char**argv){
    int a=105,b=252;
    int d=mcd(a,b);
    printf("%d",d);
}

int mcd(int a,int b){
    while(b!=0){
        int r=a%b;
        a=b;
        b=r;
    }
    return a;
}