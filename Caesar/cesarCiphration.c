#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<wchar.h>
#include<locale.h>
#define PRINTABLE_MIN 32
#define PRINTABLE_MAX 255
#define PRINTABLE_RANGE (PRINTABLE_MAX - PRINTABLE_MIN + 1)
#define UNICODE_MAX 0x10FFFF
typedef struct message
{
    size_t capacity;
    size_t size;
    wchar_t*message;
    wchar_t *encrypted;
    wchar_t *decrypted;
    int key;
}message;

void CaesarEncrypthion(message *cadena);
void CaesarDesEncryption(message *cadena);
message getMessage();
int main(){
    setlocale(LC_ALL, "es_ES.UTF-8");


 srand(time(NULL));
  message mensaje_enviado=getMessage();
  CaesarEncrypthion(&mensaje_enviado);
  CaesarDesEncryption(&mensaje_enviado);
  wprintf(L"Mensaje enviado: %ls\n", mensaje_enviado.message);
  wprintf(L"Mensaje encriptado: %ls\n", mensaje_enviado.encrypted);
  wprintf(L"Mensaje desencriptado: %ls\n", mensaje_enviado.decrypted);

  free(mensaje_enviado.message);
  free(mensaje_enviado.encrypted);
  free(mensaje_enviado.decrypted);
  return 0;
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
void CaesarEncrypthion(message *cadena){
    cadena->encrypted = (wchar_t *) malloc((cadena->size + 1) * sizeof(wchar_t));
    if (cadena->encrypted == NULL) {
        wprintf(L"No se pudo reservar memoria");
        return;
    }
    cadena->key = rand() % PRINTABLE_RANGE;
    for (size_t i = 0; i < cadena->size; i++) {
        wchar_t ch = cadena->message[i];
        if (ch >= PRINTABLE_MIN && ch <= PRINTABLE_MAX) {
            cadena->encrypted[i] = (wchar_t)(
                PRINTABLE_MIN + (ch - PRINTABLE_MIN + cadena->key) % PRINTABLE_RANGE
            );
        } else {
            cadena->encrypted[i] = ch;
        }
    }
    cadena->encrypted[cadena->size] = L'\0';
}
void CaesarDesEncryption(message *cadena){
    cadena->decrypted=(wchar_t *) malloc((cadena->size+1)*sizeof(wchar_t));
    if(cadena->decrypted==NULL){
        wprintf(L"No se pudo reservar memoria");
        return;
    }

    for (size_t i = 0; i < cadena->size; i++)
    {
        wchar_t c=cadena->encrypted[i];
        if(c<=UNICODE_MAX){
            int diff=c-cadena->key;
            if(diff<0)
                diff+=(UNICODE_MAX+1);
            cadena->decrypted[i]=(wchar_t)diff;
        }
        else{
            cadena->decrypted[i]=c;
        }
    }
     cadena->decrypted[cadena->size]=L'\0';
}