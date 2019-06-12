Obliv-C with TLS support
===============================================

This repository contains a modified version of Obliv-C with TLS support.

The original Obliv-C can be found here: https://github.com/samee/obliv-c

In particular, two parties in the secure computation share a pre-shared secret key and use the TLS protocol for network communication.

# Installation
Please follow the original Obliv-C installation instructions. 

In addition, we require `tcmalloc`, which is part of Google's [gperftools](https://github.com/gperftools/gperftools). 

For Ubuntu, it can be installed using `apt-get`.

```
sudo apt-get install libgoogle-perftools-dev
```

The rest of the steps are similar with the original Obliv-C's.

# Example

A toy, insecure example to set up the TLS connections is as follow:

```
void ocTestUtilTcpOrDieBuffered(ProtocolDesc* pd, bool isServer, const char* remote_host, const char* port, bool isProfiled, size_t first_party_send_buffer_size, size_t second_party_send_buffer_size) {
	const char key[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
	if(isServer) {
		int res;
		res = protocolAcceptTLS2P(pd, port, key, isProfiled, first_party_send_buffer_size);
		if(res!=0) {
			fprintf(stderr,"TLS accept failed\n");
			exit(1);
		}
	} else {
		int res;
		res = protocolConnectTLS2P(pd, remote_host, port, key, isProfiled, second_party_send_buffer_size);
		if (res!=0) {
			fprintf(stderr,"TLS connect failed\n");
			exit(1);
		}
	}
}	
```

Note that `key` is the pre-shared secret key. One should better not hard-code this key in the code.

Buffering is crucial for the performance since every TLS packet needs to carry additional payload. Thus, the buffer sizes need to be provided. Some of our experiments use `32768` and yield a good result.

# Licenses

Note that this library is based on CIL and Obliv-C. They both use BSD licenses.

See [LICENSE-cil](LICENSE-cil) and [LICENSE-oblivcc](LICENSE-oblivcc) for more information.