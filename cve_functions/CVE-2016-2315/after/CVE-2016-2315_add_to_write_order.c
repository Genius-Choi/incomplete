static inline void add_to_write_order(struct object_entry **wo,
			       unsigned int *endp,
			       struct object_entry *e)
{
	if (e->filled)
		return;
	wo[(*endp)++] = e;
	e->filled = 1;
}
