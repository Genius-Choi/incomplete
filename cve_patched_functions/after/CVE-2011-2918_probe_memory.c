unsigned long probe_memory(void)
{
	unsigned long total = 0;
	int i;

	for (i = 0; sp_banks[i].num_bytes; i++)
		total += sp_banks[i].num_bytes;

	return total;
}
