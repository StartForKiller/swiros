#ifndef __STDDEF_H__
	#define __STDDEF_H__

	#include <swiros/config.h>
	#include <asm/stddef.h>

	#ifdef __cplusplus
		extern "C" {
	#endif

	#define NULL 		((void*) 0)

	#define per_core(name)	name
	#define CORE_ID		0

	/** @brief String to long
	 *
	 * @return Long value of the parsed numerical string
	 */
	long strtol(const char* str, char** endptr, int base);

	/** @brief String to unsigned long
	 *
	 * @return Unsigned long value of the parsed numerical string
	 */
	unsigned long strtoul(const char* nptr, char** endptr, int base);

	/** @brief ASCII to integer
	 *
	 * Convenience function using strtol().
	 *
	 * @return Integer value of the parsed numerical string
	 */
	static inline int atoi(const char *str)
	{
		return (int)strtol(str, (char **)NULL, 10);
	}


	#ifdef __cplusplus
		}
	#endif

#endif
