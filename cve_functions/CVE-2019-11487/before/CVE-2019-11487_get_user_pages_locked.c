long get_user_pages_locked(unsigned long start, unsigned long nr_pages,
			   unsigned int gup_flags, struct page **pages,
			   int *locked)
{
	return __get_user_pages_locked(current, current->mm, start, nr_pages,
				       pages, NULL, locked,
				       gup_flags | FOLL_TOUCH);
}
