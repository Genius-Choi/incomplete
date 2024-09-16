int fixup_user_fault(struct task_struct *tsk, struct mm_struct *mm,
		     unsigned long address, unsigned int fault_flags)
{
	struct vm_area_struct *vma;
	int ret;

	vma = find_extend_vma(mm, address);
	if (!vma || address < vma->vm_start)
		return -EFAULT;

	ret = handle_mm_fault(mm, vma, address, fault_flags);
	if (ret & VM_FAULT_ERROR) {
		if (ret & VM_FAULT_OOM)
			return -ENOMEM;
		if (ret & (VM_FAULT_HWPOISON | VM_FAULT_HWPOISON_LARGE))
			return -EHWPOISON;
		if (ret & VM_FAULT_SIGBUS)
			return -EFAULT;
		BUG();
	}
	if (tsk) {
		if (ret & VM_FAULT_MAJOR)
			tsk->maj_flt++;
		else
			tsk->min_flt++;
	}
	return 0;
}
