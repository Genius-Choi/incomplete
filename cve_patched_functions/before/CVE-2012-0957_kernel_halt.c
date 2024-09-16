void kernel_halt(void)
{
	kernel_shutdown_prepare(SYSTEM_HALT);
	syscore_shutdown();
	printk(KERN_EMERG "System halted.\n");
	kmsg_dump(KMSG_DUMP_HALT);
	machine_halt();
}
