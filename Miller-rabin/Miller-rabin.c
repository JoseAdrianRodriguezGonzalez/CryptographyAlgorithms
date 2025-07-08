#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
uint64_t mod_exp(uint64_t n,uint64_t exp,uint64_t mod);
int is_probable_prime(uint64_t n,uint64_t k);
int main(){
    srand(time(NULL));
    uint64_t num;
    printf("Ingresa un número: ");
    scanf("%llu", &num);

    if (is_probable_prime(num, 10))
        printf("%llu es probablemente primo.\n", num);
    else
        printf("%llu es compuesto.\n", num);

    return 0;
}
uint64_t mod_exp(uint64_t n,uint64_t exp,uint64_t mod){
    uint64_t result =1;
    n%=mod;
    while(exp>0){
        if(exp&1) result=(result*n)%mod;
        n=(n*n)%mod;
        exp>>=1;
    }
    return result;
}
int is_probable_prime(uint64_t n,uint64_t k){
    if(n<=1) return 0;
    if(n==2 || n==3) return 1;
    if(!(n%2)) return 0;
    int s=0;
    uint64_t d=n-1;
    while(d%2==0){
        d>>=1;
        s++;
    }   
    for(int i=0;i<k;i++){
        uint64_t a=2+rand()%(n-3);
        uint64_t x=mod_exp(a,d,n);
        if(x==1 || x==(n-1)) continue;
        int continue_loop=0;
        for(int r=1;r<s;r++){
            x=mod_exp(x,2,n);
            if(x==(n-1)){
                continue_loop=1;
                break;
            } 
        }
        if(!continue_loop) return 0;
    }
    return 1;
}