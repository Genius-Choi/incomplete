int kgdb_skipexception(int exception, struct pt_regs *regs)
{
	if (exception == 3 && kgdb_isremovedbreak(regs->ip - 1)) {
		regs->ip -= 1;
		return 1;
	}
	return 0;
}
