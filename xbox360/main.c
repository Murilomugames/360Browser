
#include <stdint.h>
#include "xsdk/gpu.h"
#include "xsdk/kernel.h"
#include "xsdk/log.h"
#include "xsdk/present.h"
#include "xsdk/splash.h"

#define SCREEN_COLOR 0xFF102850

int main(void)
{
    xsdk_log_write("360Browser: iniciando...");

    xsdk_splash_show(1500);

    NTSTATUS status = xsdk_gpu_open();

    if (!NT_SUCCESS(status)) {
        xsdk_log_write("Erro ao iniciar GPU!");
        return 1;
    }

    uint32_t width = 0;
    uint32_t height = 0;

    status = xsdk_present_open(
        XSDK_DISPLAY_720P,
        2,
        1,
        &width,
        &height
    );

    if (!NT_SUCCESS(status)) {
        xsdk_gpu_close();
        return 1;
    }

    xsdk_log_write("360Browser iniciado!");

    while (1) {
        INPUT_STATE input = {0};

        if (XamInputGetState(0, 0, &input) == ERROR_SUCCESS) {
            if (input.gamepad.buttons & INPUT_GAMEPAD_BACK)
                break;
        }

        uint32_t address;

        status = xsdk_present_begin(&address, 5000);

        if (!NT_SUCCESS(status))
            break;

        xsdk_gpu_resolve(
            address,
            width,
            height,
            SCREEN_COLOR
        );

        xsdk_present_end();
    }

    xsdk_present_close();
    xsdk_gpu_close();

    xsdk_log_write("360Browser encerrado!");

    return 0;
}
