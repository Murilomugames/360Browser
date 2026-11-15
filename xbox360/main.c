

#include <arpa/inet.h>
#include <errno.h>

#include "xsdk/log.h"
#include "network.h"

int main(void)
{
    uint32_t ipv4 = 0;

    int result = browser_network_check(&ipv4);

    if (result == 1) {
        struct in_addr address = {
            .s_addr = ipv4
        };

        char ip[INET_ADDRSTRLEN];

        if (inet_ntop(AF_INET, &address, ip, sizeof(ip))) {
            xsdk_log_write("360Browser: Xbox IP = %s", ip);
        } else {
            xsdk_log_write("360Browser: erro ao converter IP");
        }
    }
    else if (result == 0) {
        xsdk_log_write("360Browser: aguardando endereco IP");
    }
    else {
        xsdk_log_write("360Browser: erro de rede");
    }

    return 0;
}

