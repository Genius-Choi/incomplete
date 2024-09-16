static void persistent_drop_snapshot(struct dm_exception_store *store)
{
	struct pstore *ps = get_info(store);

	ps->valid = 0;
	if (write_header(ps))
		DMWARN("write header failed");
}
