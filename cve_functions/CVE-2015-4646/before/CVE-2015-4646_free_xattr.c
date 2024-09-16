void free_xattr(struct xattr_list *xattr_list, int count)
{
	int i;

	for(i = 0; i < count; i++)
		free(xattr_list[i].full_name);

	free(xattr_list);
}
