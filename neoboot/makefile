MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
# MakeFileがあるディレクトリーをさぐる
ENTRYMAIN	=main
CC			=
LD			=ld.lld
SRCS		=neoboot.c
OBJS		=$(SRCS:%.c=%.o)
EFILIB_DIR :=$(MAKEFILE_DIR)/efilib/
INCLUDE_DIR :=$(EFILIB_DIR)/inc/

CFLAGS		=-fpic -ffreestanding -fno-stack-protector -fno-stack-check -fshort-wchar -mno-red-zone -maccumulate-outgoing-args
