#include <neos/types.h>

extern void kernel_main(uint64_t frame_buffer_base,
                       uint64_t frame_buffer_size) {
  uint8_t* frame_buffer = (uint8_t*)(uintptr_t)frame_buffer_base;
  for (uint64_t i = 0; i < frame_buffer_size; ++i) {
    frame_buffer[i] = i % 256;
  }
  while (1) asm volatile("hlt");
}

