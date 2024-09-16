void ext3_journal_abort_handle(const char *caller, const char *err_fn,
		struct buffer_head *bh, handle_t *handle, int err)
{
	char nbuf[16];
	const char *errstr = ext3_decode_error(NULL, err, nbuf);

	if (bh)
		BUFFER_TRACE(bh, "abort");

	if (!handle->h_err)
		handle->h_err = err;

	if (is_handle_aborted(handle))
		return;

	printk(KERN_ERR "EXT3-fs: %s: aborting transaction: %s in %s\n",
		caller, errstr, err_fn);

	journal_abort_handle(handle);
}
