static long trusted_read(const struct key *key, char __user *buffer,
			 size_t buflen)
{
	const struct trusted_key_payload *p;
	char *ascii_buf;
	char *bufp;
	int i;

	p = dereference_key_locked(key);
	if (!p)
		return -EINVAL;
	if (!buffer || buflen <= 0)
		return 2 * p->blob_len;
	ascii_buf = kmalloc(2 * p->blob_len, GFP_KERNEL);
	if (!ascii_buf)
		return -ENOMEM;

	bufp = ascii_buf;
	for (i = 0; i < p->blob_len; i++)
		bufp = hex_byte_pack(bufp, p->blob[i]);
	if ((copy_to_user(buffer, ascii_buf, 2 * p->blob_len)) != 0) {
		kzfree(ascii_buf);
		return -EFAULT;
	}
	kzfree(ascii_buf);
	return 2 * p->blob_len;
}
