static void force_user_fault(unsigned long address, int write)
{
	struct vm_area_struct *vma;
	struct task_struct *tsk = current;
	struct mm_struct *mm = tsk->mm;
	int code;

	code = SEGV_MAPERR;

	down_read(&mm->mmap_sem);
	vma = find_vma(mm, address);
	if(!vma)
		goto bad_area;
	if(vma->vm_start <= address)
		goto good_area;
	if(!(vma->vm_flags & VM_GROWSDOWN))
		goto bad_area;
	if(expand_stack(vma, address))
		goto bad_area;
good_area:
	code = SEGV_ACCERR;
	if(write) {
		if(!(vma->vm_flags & VM_WRITE))
			goto bad_area;
	} else {
		if(!(vma->vm_flags & (VM_READ | VM_EXEC)))
			goto bad_area;
	}
	switch (handle_mm_fault(mm, vma, address, write ? FAULT_FLAG_WRITE : 0)) {
	case VM_FAULT_SIGBUS:
	case VM_FAULT_OOM:
		goto do_sigbus;
	}
	up_read(&mm->mmap_sem);
	return;
bad_area:
	up_read(&mm->mmap_sem);
	__do_fault_siginfo(code, SIGSEGV, tsk->thread.kregs, address);
	return;

do_sigbus:
	up_read(&mm->mmap_sem);
	__do_fault_siginfo(BUS_ADRERR, SIGBUS, tsk->thread.kregs, address);
}
