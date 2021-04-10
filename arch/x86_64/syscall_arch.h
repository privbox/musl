#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

#include <sys/kerncall.h>

static __inline unsigned long get_cs() {
	unsigned long ret;
	__asm__ __volatile__ ("mov %%cs, %0" : "=r"(ret) : : );
	return ret;
}

static __inline unsigned long get_cpl() {
	return get_cs() & 3;
}

static __inline int can_use_call() {
	return get_cpl() == 0;
}

static __inline long __syscall0(long n)
{
	unsigned long ret;
	if (!can_use_call()) {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	} else {
		__asm__ __volatile__ (
			"call *%2\n\t"
			ASM_ALIGN
			: "=a"(ret)
			: "a"(n), "m"(kerncall_gate)
			: "rcx", "r11", "memory"
		);
	}
	return ret;
}

static __inline long __syscall1(long n, long a1)
{
	unsigned long ret;
	if (!can_use_call()) {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
	} else {
		__asm__ __volatile__ (
			"call *%3\n\t"
			ASM_ALIGN
			: "=a"(ret)
			: "a"(n), "D"(a1), "m"(kerncall_gate)
			: "rcx", "r11", "memory"
		);
	}
	return ret;
}

static __inline long __syscall2(long n, long a1, long a2)
{
	unsigned long ret;
	if (!can_use_call()) {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
						: "rcx", "r11", "memory");
	} else {
		__asm__ __volatile__ (
			"call *%4\n\t"
			ASM_ALIGN
			: "=a"(ret)
			: "a"(n), "D"(a1), "S"(a2), "m"(kerncall_gate)
			: "rcx", "r11", "memory"
		);
	}
	return ret;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret;
	if (!can_use_call()) {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
							  "d"(a3) : "rcx", "r11", "memory");
	} else {
		__asm__ __volatile__ (
			"call *%5\n\t"
			ASM_ALIGN
			: "=a"(ret)
			: "a"(n), "D"(a1), "S"(a2), "d"(a3), "m"(kerncall_gate)
			: "rcx", "r11", "memory"
		);
	}
	return ret;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	if (!can_use_call()) {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
							  "d"(a3), "r"(r10): "rcx", "r11", "memory");
	} else {
		__asm__ __volatile__ (
			"call *%6\n\t"
			ASM_ALIGN
			: "=a"(ret)
			: "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "m"(kerncall_gate)
			: "rcx", "r11", "memory"
		);
	}
	return ret;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	if (!can_use_call()) {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
							  "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");	
	} else {
		__asm__ __volatile__ (
			"call *%7\n\t"
			ASM_ALIGN
			: "=a"(ret)
			: "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8), "m"(kerncall_gate)
			: "rcx", "r11", "memory"
		);
	}
	return ret;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	register long r9 __asm__("r9") = a6;

	if (!can_use_call()) {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
							  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
	} else {
		__asm__ __volatile__ (
			"call *%8\n\t"
			ASM_ALIGN
			: "=a"(ret)
			: "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8), "r"(r9), "m"(kerncall_gate)
			: "rcx", "r11", "memory"
		);
	}
	return ret;
}

#define VDSO_USEFUL
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6"
#define VDSO_GETCPU_SYM "__vdso_getcpu"
#define VDSO_GETCPU_VER "LINUX_2.6"

#define IPC_64 0