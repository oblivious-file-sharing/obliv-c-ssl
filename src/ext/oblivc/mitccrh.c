//The code is from EMP-toolkit (https://github.com/emp-toolkit/).

#include "mitccrh.h"
#include "aes_opt.h"

typedef struct{
	ROUND_KEYS key_schedule[KS_BATCH_N];
	int key_used;
	block start_point;
} MITCCRH;

#define GET_REAL_MITCCRH MITCCRH *mitccrh = (MITCCRH*) proxy_mitccrh->addr;

void MITCCRH_init(proxy_MITCCRH *proxy_mitccrh){
	proxy_mitccrh->addr = malloc(sizeof(MITCCRH));
	
	GET_REAL_MITCCRH
	mitccrh->key_used = KS_BATCH_N;
}

void MITCCRH_setS(proxy_MITCCRH *proxy_mitccrh, block sin) {
	GET_REAL_MITCCRH
	mitccrh->start_point = sin;
}

void MITCCRH_renew_ks_if_needed(proxy_MITCCRH *proxy_mitccrh, uint64_t gid) {
	GET_REAL_MITCCRH
	
	if(mitccrh->key_used == KS_BATCH_N) {
		MITCCRH_renew_ks(proxy_mitccrh, gid);
	}
}

void MITCCRH_renew_ks_if_needed_2_keys(proxy_MITCCRH *proxy_mitccrh, uint64_t gid) {
	GET_REAL_MITCCRH
	
	if(mitccrh->key_used == KS_BATCH_N || mitccrh->key_used == KS_BATCH_N - 1) {
		MITCCRH_renew_ks(proxy_mitccrh, gid);
	}
}

void MITCCRH_renew_ks(proxy_MITCCRH *proxy_mitccrh, uint64_t gid) {
	GET_REAL_MITCCRH
	switch(KS_BATCH_N) {
		case 2:
			AES_ks2_index(mitccrh->start_point, gid, mitccrh->key_schedule); break;
		case 4:
			AES_ks4_index(mitccrh->start_point, gid, mitccrh->key_schedule); break;
		case 8:
			AES_ks8_index(mitccrh->start_point, gid, mitccrh->key_schedule); break;
		default:
			abort();
	}
	mitccrh->key_used = 0;
}

void MITCCRH_k1_h1(proxy_MITCCRH *proxy_mitccrh, block A, block *H) {
	GET_REAL_MITCCRH
	
	block keys[1], masks[1];
	keys[0] = sigma(A);
	masks[0] = keys[0];
	
	AES_ecb_ccr_ks1_enc1(keys, keys, &mitccrh->key_schedule[mitccrh->key_used]);
	mitccrh->key_used ++;
	
	H[0] = xorBlocks(keys[0], masks[0]);
}

void MITCCRH_k1_h2(proxy_MITCCRH *proxy_mitccrh, block A, block B, block *H) {
	GET_REAL_MITCCRH
	
	block keys[2], masks[2];
	keys[0] = sigma(A);
	keys[1] = sigma(B);
	masks[0] = keys[0];
	masks[1] = keys[1];
	
	AES_ecb_ccr_ks1_enc2(keys, keys, &mitccrh->key_schedule[mitccrh->key_used]);
	mitccrh->key_used ++;
	
	H[0] = xorBlocks(keys[0], masks[0]);
	H[1] = xorBlocks(keys[1], masks[1]);
}

void MITCCRH_k2_h2(proxy_MITCCRH *proxy_mitccrh, block A, block B, block *H) {
	GET_REAL_MITCCRH
	
	block keys[2], masks[2];
	keys[0] = sigma(A);
	keys[1] = sigma(B);
	masks[0] = keys[0];
	masks[1] = keys[1];

	AES_ecb_ccr_ks2_enc2(keys, keys, &mitccrh->key_schedule[mitccrh->key_used]);
	mitccrh->key_used += 2;

	H[0] = xorBlocks(keys[0], masks[0]);
	H[1] = xorBlocks(keys[1], masks[1]);
}

void MITCCRH_k2_h4(proxy_MITCCRH *proxy_mitccrh, block A0, block A1, block B0, block B1, block *H) {
	GET_REAL_MITCCRH
	block keys[4], masks[4];
	keys[0] = sigma(A0);
	keys[1] = sigma(A1);
	keys[2] = sigma(B0);
	keys[3] = sigma(B1);
	memcpy(masks, keys, sizeof keys);

	AES_ecb_ccr_ks2_enc4(keys, keys, &mitccrh->key_schedule[mitccrh->key_used]);
	mitccrh->key_used += 2;

	H[0] = xorBlocks(keys[0], masks[0]);
	H[1] = xorBlocks(keys[1], masks[1]);
	H[2] = xorBlocks(keys[2], masks[2]);
	H[3] = xorBlocks(keys[3], masks[3]);
}