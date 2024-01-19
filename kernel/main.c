#include <neos/types.h>

#define UART_ADDR               (0x03f8)
#define UART_THR                (UART_ADDR + 0x00)
#define UART_RBR                (UART_ADDR + 0x00)
#define UART_IER                (UART_ADDR + 0x01)
#define UART_FCR                (UART_ADDR + 0x02)
#define UART_LSR                (UART_ADDR + 0x05)
#define UART_LSR_RX_READY       (1 << 0)
#define UART_LSR_TX_READY       (1 << 5)
#define UART_FCR_FIFO_ENABLE    (1 << 0)
#define UART_FCR_FIFO_CLEAR     (0b11 << 1)

void mmio_write8_paddr(uint16_t paddr, uint8_t val) {
    __asm__ __volatile__ (
        "mov dx, di\n"
        "mov al, sil\n"
        "out dx, al\n"
        :
        :
        : "rdx", "rax"
    );
}

void arch_serial_write(char ch) {
    while ((mmio_read8_paddr(UART_LSR) & UART_LSR_TX_READY) == 0);
    mmio_write8_paddr(UART_THR, ch);
}

extern void kernel_main(void) {
    char a = 'a';
    arch_serial_write(a);
    while(1) __asm__ ("hlt");
}

