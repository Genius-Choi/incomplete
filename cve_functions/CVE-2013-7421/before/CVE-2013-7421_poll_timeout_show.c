static ssize_t poll_timeout_show(struct bus_type *bus, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%llu\n", poll_timeout);
}
