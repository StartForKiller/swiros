#ifndef __ARCH_VGA_H__
	#define __ARCH_VGA_H__
	
	#include <swiros/stddef.h>
	
	#ifdef __cplusplus
		extern "C" {
	#endif
	
	void vga_init(void);
	int vga_puts(const char *text);
	int vga_putchar(unsigned char c);
	void vga_cls(void);
	
	#ifdef __cplusplus
		}
	#endif

#endif
