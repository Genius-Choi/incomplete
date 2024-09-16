char *dbg_get_reg(int regno, void *mem, struct pt_regs *regs)
{
	if (regno == GDB_ORIG_AX) {
		memcpy(mem, &regs->orig_ax, sizeof(regs->orig_ax));
		return "orig_ax";
	}
	if (regno >= DBG_MAX_REG_NUM || regno < 0)
		return NULL;

	if (dbg_reg_def[regno].offset != -1)
		memcpy(mem, (void *)regs + dbg_reg_def[regno].offset,
		       dbg_reg_def[regno].size);

#ifdef CONFIG_X86_32
	switch (regno) {
	case GDB_SS:
		if (!user_mode_vm(regs))
			*(unsigned long *)mem = __KERNEL_DS;
		break;
	case GDB_SP:
		if (!user_mode_vm(regs))
			*(unsigned long *)mem = kernel_stack_pointer(regs);
		break;
	case GDB_GS:
	case GDB_FS:
		*(unsigned long *)mem = 0xFFFF;
		break;
	}
#endif
	return dbg_reg_def[regno].name;
}
