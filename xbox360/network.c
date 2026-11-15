

#include "network.h"

#include <errno.h>
#include <xsdk/net.h>

int browser_network_check(uint32_t *ipv4)
{
    if (ipv4 == 0)
        return -1;

    struct in_addr address = {0};

    // Inicia a rede e consulta o IP do Xbox.
    int result = xsdk_net_address(&address);

    if (result == 0 && address.s_addr != 0) {
        *ipv4 = address.s_addr;
        return 1;
    }

    if (result == EAGAIN || result == EADDRNOTAVAIL)
        return 0;

    return -1;
}
