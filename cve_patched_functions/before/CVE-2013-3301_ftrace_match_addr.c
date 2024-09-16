ftrace_match_addr(struct ftrace_hash *hash, unsigned long ip, int remove)
{
	struct ftrace_func_entry *entry;

	if (!ftrace_location(ip))
		return -EINVAL;

	if (remove) {
		entry = ftrace_lookup_ip(hash, ip);
		if (!entry)
			return -ENOENT;
		free_hash_entry(hash, entry);
		return 0;
	}

	return add_hash_entry(hash, ip);
}
