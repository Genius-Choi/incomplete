static int __writepage(struct page *page, struct writeback_control *wbc,
		       void *data)
{
	struct address_space *mapping = data;
	int ret = ext4_writepage(page, wbc);
	mapping_set_error(mapping, ret);
	return ret;
}
