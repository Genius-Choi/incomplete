static int __init set_uhash_entries(char *str)
{
	if (!str)
		return 0;
	uhash_entries = simple_strtoul(str, &str, 0);
	if (uhash_entries && uhash_entries < UDP_HTABLE_SIZE_MIN)
		uhash_entries = UDP_HTABLE_SIZE_MIN;
	return 1;
}
