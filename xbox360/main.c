
#include <arpa/inet.h>
#include <xsdk/log.h>
#include <xsdk/thread.h>

#include "network.h"

int main(void)
{
    uint32_t ipv4 = 0;
    int last_result = -2;

    xsdk_log_write("360Browser: iniciando rede...");

    while (1)
    {
        int result = browser_network_check(&ipv4);

        if (result != last_result)
        {
            if (result == 1)
            {
                struct in_addr address = {
                    .s_addr = ipv4
                };

                char ip[INET_ADDRSTRLEN];

                if (inet_ntop(AF_INET, &address, ip, sizeof(ip)))
                    xsdk_log_write("360Browser: IP recebido: %s", ip);
                else
                    xsdk_log_write("360Browser: IP recebido!");

            }
            else if (result == 0)
            {
                xsdk_log_write("360Browser: aguardando IP...");
            }
            else
            {
                xsdk_log_write("360Browser: erro ao iniciar rede");
            }

            last_result = result;
        }

        if (result == 1)
            break;

        xsdk_thread_sleep(1000);
    }

    xsdk_log_write("360Browser: rede inicializada!");

    // Mantém o aplicativo aberto.
    while (1)
        xsdk_thread_sleep(1000);

    return 0;
}
