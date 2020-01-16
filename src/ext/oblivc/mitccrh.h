//The code is from EMP-toolkit (https://github.com/emp-toolkit/).


#ifndef MITCCRH_H__
#define MITCCRH_H__
#include <stdio.h>

typedef struct{
	char* addr;
} proxy_MITCCRH;

typedef long long __m128i __attribute__ ((__vector_size__ (16), __may_alias__));
typedef __m128i block;

void MITCCRH_init(proxy_MITCCRH *proxy_mitccrh);
void MITCCRH_setS(proxy_MITCCRH *proxy_mitccrh, __m128i sin);
void MITCCRH_renew_ks_if_needed(proxy_MITCCRH *proxy_mitccrh, __uint64_t gid);
void MITCCRH_renew_ks(proxy_MITCCRH *proxy_mitccrh, __uint64_t gid);
void MITCCRH_k1_h1(proxy_MITCCRH *proxy_mitccrh, __m128i A, __m128i *H);
void MITCCRH_k2_h2(proxy_MITCCRH *proxy_mitccrh, __m128i A, __m128i B, __m128i *H);
void MITCCRH_k2_h4(proxy_MITCCRH *proxy_mitccrh, __m128i A0, __m128i A1, __m128i B0, __m128i B1, __m128i *H);

#endif