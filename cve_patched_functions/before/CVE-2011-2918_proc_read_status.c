static int proc_read_status(char *page, char **start, off_t off, int count,
			    int *eof, void *data)
{
	char *p = page;
	int len;

	p += sprintf(p, "Emulated SWP:\t\t%lu\n", swpcounter);
	p += sprintf(p, "Emulated SWPB:\t\t%lu\n", swpbcounter);
	p += sprintf(p, "Aborted SWP{B}:\t\t%lu\n", abtcounter);
	if (previous_pid != 0)
		p += sprintf(p, "Last process:\t\t%d\n", previous_pid);

	len = (p - page) - off;
	if (len < 0)
		len = 0;

	*eof = (len <= count) ? 1 : 0;
	*start = page + off;

	return len;
}
