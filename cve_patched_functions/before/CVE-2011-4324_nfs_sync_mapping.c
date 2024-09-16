int nfs_sync_mapping(struct address_space *mapping)
{
	int ret;

	if (mapping->nrpages == 0)
		return 0;
	unmap_mapping_range(mapping, 0, 0, 0);
	ret = filemap_write_and_wait(mapping);
	if (ret != 0)
		goto out;
	ret = nfs_wb_all(mapping->host);
out:
	return ret;
}
