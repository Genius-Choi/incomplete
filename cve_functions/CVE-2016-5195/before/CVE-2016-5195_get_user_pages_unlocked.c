long get_user_pages_unlocked(unsigned long start, unsigned long nr_pages,
			     int write, int force, struct page **pages)
{
	return __get_user_pages_unlocked(current, current->mm, start, nr_pages,
					 write, force, pages, FOLL_TOUCH);
}
