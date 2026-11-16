
#include <stdint.h>

#include "xsdk/gpu.h"
#include "xsdk/kernel.h"
#include "xsdk/log.h"
#include "xsdk/present.h"
#include "xsdk/text.h"

enum
{
    BUFFERS = 2,
    SWAP_INTERVAL = 1,
    BEGIN_TIMEOUT_MS = 5000
};

int main(void)
{
    xsdk_log_write("360Browser: iniciando interface");

    // Inicializa a GPU.
    NTSTATUS status = xsdk_gpu_open();

    if (!NT_SUCCESS(status))
    {
        xsdk_log_write("Erro ao iniciar GPU: 0x%08X",
                       (unsigned)status);
        return 1;
    }

    // Inicializa o sistema de textos.
    status = xsdk_text_open();

    if (!NT_SUCCESS(status))
    {
        xsdk_log_write("Erro ao iniciar textos: 0x%08X",
                       (unsigned)status);

        xsdk_gpu_close();
        return 1;
    }

    // Abre a tela do Xbox.
    uint32_t width = 0;
    uint32_t height = 0;

    status = xsdk_present_open(
        XSDK_DISPLAY_720P,
        BUFFERS,
        SWAP_INTERVAL,
        &width,
        &height
    );

    if (!NT_SUCCESS(status))
    {
        xsdk_log_write("Erro ao abrir tela: 0x%08X",
                       (unsigned)status);

        xsdk_text_close();
        xsdk_gpu_close();
        return 1;
    }

    xsdk_log_write("360Browser: tela aberta %ux%u",
                   (unsigned)width,
                   (unsigned)height);

    // A primeira imagem prepara o fundo branco.
    int first_frame = 1;

    // Loop principal do navegador.
    while (1)
    {
        INPUT_STATE input = {0};

        uint32_t input_result =
            XamInputGetState(0, 0, &input);

        if (input_result != ERROR_SUCCESS)
        {
            input = (INPUT_STATE){0};
        }

        // Botao BACK fecha o navegador.
        if (input.gamepad.buttons & INPUT_GAMEPAD_BACK)
        {
            break;
        }

        uint32_t address = 0;

        status = xsdk_present_begin(
            &address,
            BEGIN_TIMEOUT_MS
        );

        if (!NT_SUCCESS(status))
        {
            xsdk_log_write("Erro ao preparar imagem: 0x%08X",
                           (unsigned)status);
            break;
        }

        xsdk_gpu_set_target(width, height);

        if (first_frame)
        {
            // Fundo branco.
            xsdk_gpu_resolve(
                address,
                width,
                height,
                0xFFFFFFFF
            );

            first_frame = 0;
        }
        else
        {
            // Nome do navegador.
            xsdk_text_draw(
                80, 80, 4,
                0xFF168A42,
                "360Browser"
            );

            // Descricao.
            xsdk_text_draw(
                84, 170, 2,
                0xFF202020,
                "Seu navegador no Xbox 360"
            );

            // Mensagem de desenvolvimento.
            xsdk_text_draw(
                84, 220, 2,
                0xFF168A42,
                "Interface em desenvolvimento"
            );

            // Envia a imagem para a tela.
            xsdk_gpu_resolve(
                address,
                width,
                height,
                0xFFFFFFFF
            );
        }

        xsdk_present_end();
    }

    // Encerra os sistemas graficos.
    xsdk_present_close();
    xsdk_text_close();

    status = xsdk_gpu_close();

    if (!NT_SUCCESS(status))
    {
        xsdk_log_write("Erro ao fechar GPU: 0x%08X",
                       (unsigned)status);
    }

    xsdk_log_write("360Browser: encerrado");

    return 0;
}

