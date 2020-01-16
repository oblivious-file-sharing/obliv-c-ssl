#include <common_util.h>

void ocTlsOrDieBuffered(ProtocolDesc *pd, const char* remote_host, const char *port, size_t first_party_send_buffer_size, size_t second_party_send_buffer_size){
	const char key[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
	
	if(!remote_host) {
		if(protocolAcceptTLS2P(pd, port, key, false, first_party_send_buffer_size) != 0) {
			fprintf(stderr, "\033[0;31m[ERROR]\033[0m TLS accept failed\n");
			exit(1);
		}
	} else if(protocolConnectTLS2P(pd, remote_host, port, key, false, second_party_send_buffer_size) != 0) {
		fprintf(stderr, "\033[0;31m[ERROR]\033[0m TLS connect failed\n");
		exit(1);
	}
}