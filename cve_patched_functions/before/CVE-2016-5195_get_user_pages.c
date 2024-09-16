long get_user_pages(unsigned long start, unsigned long nr_pages,
		int write, int force, struct page **pages,
		struct vm_area_struct **vmas)
{
	return __get_user_pages_locked(current, current->mm, start, nr_pages,
				       write, force, pages, vmas, NULL, false,
				       FOLL_TOUCH);
}
