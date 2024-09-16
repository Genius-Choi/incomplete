xalloc(unsigned long size)
{
	void *mem = malloc(size);

	if (mem == NULL) {
		if (__test_bit(DONT_FORK_BIT, &debug))
			perror("Keepalived");
		else
			log_message(LOG_INFO, "Keepalived xalloc() error - %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

#ifdef _MEM_CHECK_
	mem_allocated += size - sizeof(long);
	if (mem_allocated > max_mem_allocated)
		max_mem_allocated = mem_allocated;
#endif

	return mem;
}
