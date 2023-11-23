MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
# General
ENTRYMAIN	=main
PROGRAM		=neoboot
SRCS		=neoboot.c
OBJS		=$(SRCS:%.c=%.o)
EFILIB_DIR :=$(MAKEFILE_DIR)/efilib/
INCLUDE_DIR :=$(EFILIB_DIR)/inc/

#FLAGS AND TOOLS
CC			=/opt/local/bin/x86_64-elf-gcc
LD			=/opt/local/bin/x86_64-elf-ld
OBJCOPY     =/opt/local/bin/x86_64-elf-objcopy

CFLAGS		=-fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args
LDFLAGS     =-shared -Bsymbolic -L$(GNU_EFI_DIR)/x86_64/lib -L$(GNU_EFI_DIR)/x86_64/gnuefi -T$(GNU_EFI_DIR)/gnuefi/elf_x86_64_efi.lds
OBJCOPYFLAGS = -j .text -j .sdata -j .data -j .dynamic -j .dynsym  -j .rel -j .rela -j .rel.* -j .rela.* -j .reloc --target efi-app-x86_64 --subsystem=10

#Library
LIBS        =-lgnuefi -lefi

all: $(PROGRAM).efi

$(OBJS): $(SRCS)
	$(CC) $(INCLUDE_DIR) $(CFLAGS) -c $(SRCS)

$(PROGRAM).so : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(EFILIB_DIR)/x86_64/gnuefi/crt0-efi-x86_64.o -o $(PROGRAM).so $(LIBS)

$(PROGRAM).efi: $(PROGRAM).so
	$(OBJCOPY) $(OBJCOPYFLAGS) $(PROGRAM).so $(PROGRAM).efi

clean:
	rm $(OBJS) $(PROGRAM).so $(PROGRAM).efi