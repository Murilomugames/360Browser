
#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

/*
 * Retorno:
 *  1 = endereço IP disponível
 *  0 = aguardando endereço IP
 * -1 = erro
 */
int browser_network_check(uint32_t *ipv4);

#endif
