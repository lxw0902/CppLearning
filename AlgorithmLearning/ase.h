#ifndef ASE_H
#define ASE_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
void inv_cipher(uint8_t *in, uint8_t *out, uint8_t *w);
void key_expansion(uint8_t *key, uint8_t *w);
void cipher(uint8_t *in, uint8_t *out, uint8_t *w);

void set_Nb(int v);
void set_Nr(int v);
void set_Nk(int v);
int get_Nb();
int get_Nr();
int get_Nk();


void AESTest();

#ifdef __cplusplus
}
#endif

#endif // ASE_H
