static void persistent_dtr(struct dm_exception_store *store)
{
	struct pstore *ps = get_info(store);

	destroy_workqueue(ps->metadata_wq);

	/* Created in read_header */
	if (ps->io_client)
		dm_io_client_destroy(ps->io_client);
	free_area(ps);

	/* Allocated in persistent_read_metadata */
	if (ps->callbacks)
		vfree(ps->callbacks);

	kfree(ps);
}
