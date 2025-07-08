#include "./lib/crypt.h"
typedef struct{
    uint64_t n;
    uint64_t c;
    uint64_t d;
}RSA;


RSA RSAencrypt(int bitlength);
void RSA_encrypt_message(message* cadena,RSA key);
void RSA_decrypt_message(message* cadena,RSA key);
uint64_t mod_inverse(uint64_t a, uint64_t m);
int main(){
    setlocale(LC_ALL,"es_ES.UTF-8");
    srand(time(NULL));
    message mensaje_enviado=getMessage();
    RSA key=RSAencrypt(15);
    
    RSA_encrypt_message(&mensaje_enviado,key);
    RSA_decrypt_message(&mensaje_enviado,key);
    wprintf(L"Mensaje original: %ls\n", mensaje_enviado.message);
    printf("Mensaje cifrado (decimal): ");
    for (size_t i = 0; i < mensaje_enviado.size; i++) {
        printf("%llu ", mensaje_enviado.encrypted[i]);
    }
    printf("\n");
    wprintf(L"Mensaje descifrado: %ls\n", mensaje_enviado.decrypted);

    free(mensaje_enviado.message);
    free(mensaje_enviado.encrypted);
    free(mensaje_enviado.decrypted);
    return 0;
}
RSA RSAencrypt(int bitlength){
    uint64_t p=generate_prime(bitlength,10);
    uint64_t q=generate_prime(bitlength,10);
    uint64_t n=p*q;
    uint64_t phi=(p-1)*(q-1);
    uint64_t c=0;
    do{
        c=random_odd_integer(bitlength);
    }while((!((c > 1) && (c < phi)) || (mcd(c, phi) != 1)));
    uint64_t d=mod_inverse(c,phi);
    printf("p1=%llu\n", p);
    printf("q1=%llu\n", q);
    printf("n=%llu\n", n);
    printf("phi=%llu\n", phi);
    printf("c=%llu\n", c);
    printf("d=%llu\n", d);
    RSA result={n,c,d};
    return result;
}

void RSA_encrypt_message(message* cadena,RSA key){
    cadena->encrypted=(uint64_t*)malloc(cadena->size*sizeof(uint64_t));
    for(size_t i=0;i<cadena->size;i++)
        cadena->encrypted[i]=mod_exp((uint64_t)cadena->message[i],key.c,key.n);
    
}
void RSA_decrypt_message(message* cadena,RSA key){
    cadena->decrypted=(wchar_t*)malloc(cadena->size*sizeof(wchar_t));
    for(size_t i=0;i<cadena->size;i++)
        cadena->decrypted[i] = (wchar_t)mod_exp(cadena->encrypted[i], key.d, key.n);
    
    cadena->decrypted[cadena->size]=L'\0';
}
uint64_t mod_inverse(uint64_t a, uint64_t m){
    Result r = Euclidean(a, m);
    int64_t x = r.x;
    if (x < 0) x += (int64_t)m;
    return (uint64_t)x;
}
