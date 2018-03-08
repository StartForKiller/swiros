#include <swiros/stddef.h>
#include <swiros/stdio.h>
#include <swiros/string.h>

extern const void kernel_start;
extern const void kernel_end;
extern const void bss_start;
extern const void bss_end;
extern char __BUILD_DATE;
extern char __BUILD_TIME;

int main(void)
{
	memset((void*)&bss_start, 0x00, ((size_t) &bss_end - (size_t) &bss_start));
	koutput_init();
	
	kprintf("Version %s Build %u, %u\n", SWIROS_VERSION, &__BUILD_DATE, &__BUILD_TIME);
	
	while(1) { 
		
	}
	
	return 0;
}
