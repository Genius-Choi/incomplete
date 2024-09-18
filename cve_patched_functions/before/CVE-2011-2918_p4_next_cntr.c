static int p4_next_cntr(int thread, unsigned long *used_mask,
			struct p4_event_bind *bind)
{
	int i, j;

	for (i = 0; i < P4_CNTR_LIMIT; i++) {
		j = bind->cntr[thread][i];
		if (j != -1 && !test_bit(j, used_mask))
			return j;
	}

	return -1;
}
