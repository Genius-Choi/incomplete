static int ib_ucm_alloc_data(const void **dest, u64 src, u32 len)
{
	void *data;

	*dest = NULL;

	if (!len)
		return 0;

	data = memdup_user((void __user *)(unsigned long)src, len);
	if (IS_ERR(data))
		return PTR_ERR(data);

	*dest = data;
	return 0;
}
