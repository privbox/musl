#ifndef _MISC_SYS_KERNCALL_H
#define _MISC_SYS_KERNCALL_H
#ifndef __ASSEMBLER__
#include <stdint.h>
extern int kerncall_setup(void);
extern long kerncall_spawn(uintptr_t ptr, unsigned long arg);
extern void *kerncall_gate;
#endif
#endif /* _MISC_SYS_KERNCALL_H */