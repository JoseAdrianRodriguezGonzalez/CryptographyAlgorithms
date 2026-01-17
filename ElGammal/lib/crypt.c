#include "crypt.h"
uint64_t mcd(uint64_t a, uint64_t b){
     while(b!=0){
        uint64_t r=a%b;
        a=b;
        b=r;
    }
    return a;
}
Result Euclidean(uint64_t a,uint64_t b){
    int64_t values[4]={1,0,0,1};
    uint64_t q=0,r=0;
    while(b!=0){
        q=a/b;
        r=a%b;
        int64_t tempx=values[0]-q*values[1];
        int64_t tempy=values[2]-q*values[3];

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
void segmentedSieve(int n){
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
uint64_t random_odd_integer(int bits){
    uint64_t n = 0;
    for (int i = 0; i < bits; i += 15) {
        n = (n << 15) | (rand() & 0x7FFF);
    }
    n |= 1ULL; 
    n |= (1ULL << (bits - 1)); 
    return n;
}
uint64_t generate_prime(int bit_length,int k){
    int* primes =NULL;
    int Count=0;
    sieve_odd_bitset(10000,&primes,&Count);
    while(1){
        uint64_t n=random_odd_integer(bit_length);
        int divisible=0;
        for(int i=0;i<Count;i++){
            if(n%primes[i]==0){
                divisible=1;
                break;
            }
        }
        if(!divisible && is_probable_prime(n,k)){
            free(primes);
            return n;
        }
    }
}
message getMessage(){
  message cer1;
  cer1.capacity=10;
  cer1.size=0;  
  cer1.message=(wchar_t* )malloc(cer1.capacity*sizeof(wchar_t));
  if (cer1.message==NULL){
    wprintf(L"Error al asignar memoria");
    return cer1;
  }
  wprintf(L"Ingresa un texto: ");
  int c; 
  while ((c=getwchar())!=L'\n' && c!=WEOF){
    if(cer1.size+1>=cer1.capacity){
        cer1.capacity*=2;
        cer1.message=(wchar_t* )realloc(cer1.message,cer1.capacity*sizeof(wchar_t));
        if (cer1.message==NULL){
            wprintf(L"Error al reasignar memoria");
            return cer1;
        }     
    }
    cer1.message[cer1.size++]=(wchar_t)c;
  }
  cer1.message[cer1.size]=L'\0';
  return cer1;
}