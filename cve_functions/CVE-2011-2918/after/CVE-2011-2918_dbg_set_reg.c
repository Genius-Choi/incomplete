int dbg_set_reg(int regno, void *mem, struct pt_regs *regs)
{
	if (
#ifdef CONFIG_X86_32
	    regno == GDB_SS || regno == GDB_FS || regno == GDB_GS ||
#endif
	    regno == GDB_SP || regno == GDB_ORIG_AX)
		return 0;

	if (dbg_reg_def[regno].offset != -1)
		memcpy((void *)regs + dbg_reg_def[regno].offset, mem,
		       dbg_reg_def[regno].size);
	return 0;
}
