static void *proc_key_users_next(struct seq_file *p, void *v, loff_t *_pos)
{
	(*_pos)++;
	return key_user_next(seq_user_ns(p), (struct rb_node *)v);
}
