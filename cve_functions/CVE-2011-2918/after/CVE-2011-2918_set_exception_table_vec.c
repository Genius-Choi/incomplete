void *set_exception_table_vec(unsigned int vec, void *handler)
{
	extern void *exception_handling_table[];
	void *old_handler;

	old_handler = exception_handling_table[vec];
	exception_handling_table[vec] = handler;
	return old_handler;
}
