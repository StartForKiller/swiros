#ifndef __CONFIG_H__
	#define __CONFIG_H__
	
	#ifdef __cplusplus
		extern "C" {
	#endif
	
	#define SWIROS_VERSION "0.1"
	#define VIDEO_MEM_ADDR 0xB8000
	
	#define BYTE_ORDER LITTLE_ENDIAN
	
	#define BUILTIN_EXPECT(exp, b) __builtin_expect((exp), (b))
	#define NORETURN __attribute__((noreturn))
	#define STDCALL __attribute__((stdcall))
	
	#define HAVE_ARCH_MEMSET
    #define HAVE_ARCH_MEMCPY
	#define HAVE_ARCH_STRLEN
	#define HAVE_ARCH_STRCPY
	#define HAVE_ARCH_STRNCPY
	
	#ifdef __cplusplus
		}
	#endif
	
#endif
