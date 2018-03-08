#ifndef __STDIO_H__
	#define __STDIO_H__

	#include <swiros/config.h>
	#include <swiros/stddef.h>
	#include <swiros/stdarg.h>

	#ifdef __cplusplus
		extern "C" {
	#endif

	/*
	 * Works like the ANSI C function puts 
	 */
	int kputs(const char *);

	/*
	 * Works like the ANSI c function putchar
	 */
	int kputchar(int);

	/*
	 * Works like the ANSI C function printf
	 */
	int kprintf(const char*, ...);

	/*
	 * Initialize the I/O functions 
	 */
	int koutput_init(void);

	/*
	 * Scaled down version of printf(3)
	 */
	int kvprintf(char const *fmt, void (*func) (int, void *), void *arg, int radix, va_list ap);

	#ifdef __cplusplus
		}
	#endif

#endif
