#include <stdio.h>
#include <stdlib.h>
#include <gtmos/kernel/arch/arch.h>

__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
	panic("  The system has aborted unexceptdly.");
#else
	// TODO: Abnormally terminate the process as if by SIGABRT.
	printf("abort()\n");
#endif
	while (1) { }
	__builtin_unreachable();
}
