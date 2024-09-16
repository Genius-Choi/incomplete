__ftrace_replace_code(struct dyn_ftrace *rec, int enable)
{
	unsigned long ftrace_old_addr;
	unsigned long ftrace_addr;
	int ret;

	ret = ftrace_update_record(rec, enable);

	if (rec->flags & FTRACE_FL_REGS)
		ftrace_addr = (unsigned long)FTRACE_REGS_ADDR;
	else
		ftrace_addr = (unsigned long)FTRACE_ADDR;

	switch (ret) {
	case FTRACE_UPDATE_IGNORE:
		return 0;

	case FTRACE_UPDATE_MAKE_CALL:
		return ftrace_make_call(rec, ftrace_addr);

	case FTRACE_UPDATE_MAKE_NOP:
		return ftrace_make_nop(NULL, rec, ftrace_addr);

	case FTRACE_UPDATE_MODIFY_CALL_REGS:
	case FTRACE_UPDATE_MODIFY_CALL:
		if (rec->flags & FTRACE_FL_REGS)
			ftrace_old_addr = (unsigned long)FTRACE_ADDR;
		else
			ftrace_old_addr = (unsigned long)FTRACE_REGS_ADDR;

		return ftrace_modify_call(rec, ftrace_old_addr, ftrace_addr);
	}

	return -1; /* unknow ftrace bug */
}
