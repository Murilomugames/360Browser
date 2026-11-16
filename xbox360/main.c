
#include <stdint.h>
#include <arpa/inet.h>

#include "xsdk/log.h"
#include "xsdk/net.h"
#include "xsdk/thread.h"

#include "network.h"

int main(void)
{
    uint32_t ipv4 = 0;
    uint32_t link = 0;

    xsdk_log_write("360Browser: iniciando teste de rede");

    int link_result = xsdk_net_link(&link);

    xsdk_log_write(
        "360Browser: link status=%d, bits=0x%02X",
        link_result,
        (unsigned)link
    );

    for (int attempt = 0; attempt < 15; attempt++)
    {
        int result = browser_network_check(&ipv4);

        if (result == 1)
        {
            struct in_addr address = {
                .s_addr = ipv4
            };

            char ip[INET_ADDRSTRLEN];

            if (inet_ntop(AF_INET, &address, ip, sizeof(ip)))
                xsdk_log_write("360Browser: IP encontrado: %s", ip);

            xsdk_log_write("360Browser: teste de rede concluido!");
            return 0;
        }

        if (result == 0)
        {
            xsdk_log_write("360Browser: aguardando IP...");
        }
        else
        {
            xsdk_log_write(
                "360Browser: erro de rede: %d",
                result
            );
            return 1;
        }

        xsdk_thread_sleep(1000);
    }

    xsdk_log_write("360Browser: tempo esgotado aguardando IP");

    return 0;
}
