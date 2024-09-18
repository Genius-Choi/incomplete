int udf_build_ustr(struct ustr *dest, dstring *ptr, int size)
{
	int usesize;

	if (!dest || !ptr || !size)
		return -1;
	BUG_ON(size < 2);

	usesize = min_t(size_t, ptr[size - 1], sizeof(dest->u_name));
	usesize = min(usesize, size - 2);
	dest->u_cmpID = ptr[0];
	dest->u_len = usesize;
	memcpy(dest->u_name, ptr + 1, usesize);
	memset(dest->u_name + usesize, 0, sizeof(dest->u_name) - usesize);

	return 0;
}
