

#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

// 1 = IP recebido
// 0 = aguardando IP
// -1 = erro de rede

int browser_network_check(uint32_t *ipv4);

#endif
