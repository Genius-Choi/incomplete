asmlinkage void __div0(void)
{
	printk("Division by zero in kernel.\n");
	dump_stack();
}
