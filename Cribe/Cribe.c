#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>
#include<string.h>
#define SEGMENTED_SIZE 32768
#define SET_BIT(arr, i) (arr[(i) >> 3] |= (1 << ((i) & 7)))
#define CLEAR_BIT(arr, i) (arr[(i) >> 3] &= ~(1 << ((i) & 7)))
#define GET_BIT(arr, i) ((arr[(i) >> 3] >> ((i) & 7)) & 1)
int segmentedSieve(int n);
void sieve_odd_bitset(int limit,int** primes,int *prime_count);
int main(){
    int n=100;
    segmentedSieve(n);
    return 0;
}
void sieve_odd_bitset(int limit,int** primes,int *prime_count){
    int m=(limit-1)/2;
    char* is_prime=calloc(m,sizeof(char));
    for(int i=0;i<m;i++) is_prime[i]=1;
    for(int i=0;(2*i+3)*(2*i+3)<m;i++){
        if(is_prime[i]){
            int p=2*i+3;
            for(int j=((p*p-3)/2);j<m-1;j+=p){
                is_prime[j]=0;
            }
        }
    }
    //Count primes
    *prime_count=1;
    for(int i=0;i<m;i++) if (is_prime[i])(*prime_count)++;

    *primes=malloc((*prime_count)*sizeof(int));
    int idx=0;
    (*primes)[idx++]=2;
    for(int i=0;i<m;i++) if(is_prime[i]) (*primes)[idx++]=2*i+3;
    free(is_prime);
}
int segmentedSieve(int n){
    int limit=(int)sqrt(n);
    int* base_primes=NULL;
    int base_count=0;
    sieve_odd_bitset(limit,&base_primes,&base_count);
    int64_t low=3;
    int64_t high=low+SEGMENTED_SIZE*2-1;
    if(high>n) high=n;
    while(low<n){
        int64_t segment_len=(high-low)/2+1;
        int bytes=(segment_len+7)/8;
        uint8_t *bits=malloc(bytes);
        memset(bits,0xFF,bytes);
        for(int i=1;i<base_count;i++){
            int p=base_primes[i];
            int64_t start=((low+p-1)/p)*p;
            if(start<p*p) start=(int64_t) p*p;
            if((start&1)==0) start+=p;
            for(int64_t j=start;j<=high;j+=2*p){
                int64_t index=(j-low)/2;
                CLEAR_BIT(bits,index);
            }
        }
        for(int64_t i=0;i<segment_len;i++){
            if(GET_BIT(bits,i)) printf("%lld\n",low+2*i);
        }
        free(bits);
        low+=SEGMENTED_SIZE;
        high+=SEGMENTED_SIZE;
        if(high>n) high=n;
    }
    free(base_primes);
}