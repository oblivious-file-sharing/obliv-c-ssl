#pragma once

#include <obliv.h>
void ocTlsOrDieBuffered(ProtocolDesc *pd, const char* remote_host, const char *port, size_t first_party_send_buffer_size, size_t second_party_send_buffer_size);
