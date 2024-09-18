int proc_dostring(struct ctl_table *table, int write,
		  void __user *buffer, size_t *lenp, loff_t *ppos)
{
	if (write && *ppos && sysctl_writes_strict == SYSCTL_WRITES_WARN)
		warn_sysctl_write(table);

	return _proc_do_string((char *)(table->data), table->maxlen, write,
			       (char __user *)buffer, lenp, ppos);
}
