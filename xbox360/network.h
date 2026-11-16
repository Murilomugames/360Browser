
#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

// 1 = IP encontrado
// 0 = aguardando IP
// Outro valor = código de erro

int browser_network_check(uint32_t *ipv4);

#endif
