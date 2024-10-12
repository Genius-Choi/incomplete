sa_init(int init_service)
{
	sa_handle_impl_t impl_handle;

	impl_handle = calloc(sizeof (struct sa_handle_impl), 1);

	if (impl_handle == NULL)
		return (NULL);

	impl_handle->zfs_libhandle = libzfs_init();

	if (impl_handle->zfs_libhandle != NULL) {
		libzfs_print_on_error(impl_handle->zfs_libhandle, B_TRUE);
	}

	parse_sharetab(impl_handle);
	update_zfs_shares(impl_handle, NULL);

	return ((sa_handle_t)impl_handle);
}
