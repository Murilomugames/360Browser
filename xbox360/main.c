
#include <stdint.h>

#include "xsdk/log.h"
#include "xsdk/net.h"
#include "xsdk/thread.h"

#include "network.h"

int main(void)
{
    uint32_t ipv4 = 0;
    uint32_t link = 0;

    xsdk_log_write("360Browser iniciado!");

    xsdk_net_link(&link);

    xsdk_log_write("360Browser: verificando rede...");

    while (1)
    {
        int result = browser_network_check(&ipv4);

        if (result == 1)
        {
            xsdk_log_write("360Browser: internet conectada!");
        }
        else if (result == 0)
        {
            xsdk_log_write("360Browser: aguardando conexao...");
        }
        else
        {
            xsdk_log_write("360Browser: erro de rede!");
        }

        xsdk_thread_sleep(1000);
    }

    return 0;
}

