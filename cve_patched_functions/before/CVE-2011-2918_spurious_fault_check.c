static int spurious_fault_check(unsigned long error_code, pte_t *pte)
{
	if ((error_code & PF_WRITE) && !pte_write(*pte))
		return 0;

	if ((error_code & PF_INSTR) && !pte_exec(*pte))
		return 0;

	return 1;
}
