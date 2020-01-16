#include<stdio.h>
#include<obliv.h>

#include"million.h"

int main(int argc,char *argv[])
{
	ProtocolDesc pd;
	protocolIO io;
	if(argc < 4) {
		if(argc < 3) fprintf(stderr, "\033[0;31m[ERROR]\033[0m Port number missing\n");
		else fprintf(stderr, "\033[0;31m[ERROR]\033[0m Party missing\n");
		
		fprintf(stderr, "\033[0;32m[INFO]\033[0m Usage (Party 1): %s <money> <port> <--|remote_host>. Please use the port number 6601. \n", argv[0]);
		fprintf(stderr, "\033[0;32m[INFO]\033[0m Usage (Party 2): %s <money> <port> <--|remote_host>. Please use the port number 6601. \n", argv[0]);
		return 1;
	}
	
	const char* remote_host = (strcmp(argv[3], "--") == 0 ? NULL : argv[3]);
	int i, party = (!remote_host ? 1 : 2);
	
	sscanf(argv[1], "%d", &io.mywealth);
	ocTlsOrDieBuffered(&pd, remote_host, argv[2], 1024, 0);
	setCurrentParty(&pd, party);
	execYaoProtocol(&pd,millionaire,&io);
	cleanupProtocol(&pd);
	fprintf(stderr,"Result: %d\n",io.cmp);
	return 0;
}