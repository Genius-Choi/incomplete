__always_inline long __get_user_pages_unlocked(struct task_struct *tsk, struct mm_struct *mm,
					       unsigned long start, unsigned long nr_pages,
					       int write, int force, struct page **pages,
					       unsigned int gup_flags)
{
	long ret;
	int locked = 1;
	down_read(&mm->mmap_sem);
	ret = __get_user_pages_locked(tsk, mm, start, nr_pages, write, force,
				      pages, NULL, &locked, false, gup_flags);
	if (locked)
		up_read(&mm->mmap_sem);
	return ret;
}
