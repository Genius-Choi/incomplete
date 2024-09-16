long get_user_pages_locked(unsigned long start, unsigned long nr_pages,
			   int write, int force, struct page **pages,
			   int *locked)
{
	return __get_user_pages_locked(current, current->mm, start, nr_pages,
				       write, force, pages, NULL, locked, true,
				       FOLL_TOUCH);
}
