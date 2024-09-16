struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
{
#ifdef AT_SYSINFO_EHDR
	return &gate_vma;
#else
	return NULL;
#endif
}
