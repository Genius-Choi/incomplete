static int tty_copy_to_user(struct tty_struct *tty, void __user *to,
			    size_t tail, size_t n)
{
	struct n_tty_data *ldata = tty->disc_data;
	size_t size = N_TTY_BUF_SIZE - tail;
	const void *from = read_buf_addr(ldata, tail);
	int uncopied;

	if (n > size) {
		tty_audit_add_data(tty, from, size);
		uncopied = copy_to_user(to, from, size);
		if (uncopied)
			return uncopied;
		to += size;
		n -= size;
		from = ldata->read_buf;
	}

	tty_audit_add_data(tty, from, n);
	return copy_to_user(to, from, n);
}
