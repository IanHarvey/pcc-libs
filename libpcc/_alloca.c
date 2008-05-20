__asm(	"	.text\n"
	"	.globl __alloca\n"
	"__alloca:\n"
#ifdef __i386__
	"	pop %edx\n"
	"	pop %eax\n"
	"	add $3,%eax\n"
	"	and $-4,%eax\n"
	"1:	cmp $4096,%eax\n"
	"	jge 2f\n"
	"	sub %eax,%esp\n"
	"	test %eax,%esp\n"
	"	mov %esp,%eax\n"
	"	push %edx\n"
	"	push %edx\n"
	"	ret\n"
	"2:	sub $4096,%esp\n"
	"	sub $4096,%esp\n"
	"	test %eax,(%esp)\n"
	"	jmp 1b\n"
#endif
);

