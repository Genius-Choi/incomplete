static void dump_line(char *data, int offset, int limit)
{
	int i;
	unsigned char error = 0;
	int bad_count = 0;

	pr_err("%03x: ", offset);
	for (i = 0; i < limit; i++) {
		if (data[offset + i] != POISON_FREE) {
			error = data[offset + i];
			bad_count++;
		}
	}
	print_hex_dump(KERN_CONT, "", 0, 16, 1,
			&data[offset], limit, 1);

	if (bad_count == 1) {
		error ^= POISON_FREE;
		if (!(error & (error - 1))) {
			pr_err("Single bit error detected. Probably bad RAM.\n");
#ifdef CONFIG_X86
			pr_err("Run memtest86+ or a similar memory test tool.\n");
#else
			pr_err("Run a memory test tool.\n");
#endif
		}
	}
}
