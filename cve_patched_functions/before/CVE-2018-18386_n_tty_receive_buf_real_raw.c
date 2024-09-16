n_tty_receive_buf_real_raw(struct tty_struct *tty, const unsigned char *cp,
			   char *fp, int count)
{
	struct n_tty_data *ldata = tty->disc_data;
	size_t n, head;

	head = ldata->read_head & (N_TTY_BUF_SIZE - 1);
	n = min_t(size_t, count, N_TTY_BUF_SIZE - head);
	memcpy(read_buf_addr(ldata, head), cp, n);
	ldata->read_head += n;
	cp += n;
	count -= n;

	head = ldata->read_head & (N_TTY_BUF_SIZE - 1);
	n = min_t(size_t, count, N_TTY_BUF_SIZE - head);
	memcpy(read_buf_addr(ldata, head), cp, n);
	ldata->read_head += n;
}
