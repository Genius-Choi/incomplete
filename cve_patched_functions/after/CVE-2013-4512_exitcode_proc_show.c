static int exitcode_proc_show(struct seq_file *m, void *v)
{
	int val;

	/*
	 * Save uml_exitcode in a local so that we don't need to guarantee
	 * that sprintf accesses it atomically.
	 */
	val = uml_exitcode;
	seq_printf(m, "%d\n", val);
	return 0;
}
