static void *proc_keys_next(struct seq_file *p, void *v, loff_t *_pos)
{
	struct rb_node *n;

	n = key_serial_next(p, v);
	if (n)
		*_pos = key_node_serial(n);
	return n;
}
