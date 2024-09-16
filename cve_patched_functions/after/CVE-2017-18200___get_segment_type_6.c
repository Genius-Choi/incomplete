static int __get_segment_type_6(struct f2fs_io_info *fio)
{
	if (fio->type == DATA) {
		struct inode *inode = fio->page->mapping->host;

		if (is_cold_data(fio->page) || file_is_cold(inode))
			return CURSEG_COLD_DATA;
		if (is_inode_flag_set(inode, FI_HOT_DATA))
			return CURSEG_HOT_DATA;
		return CURSEG_WARM_DATA;
	} else {
		if (IS_DNODE(fio->page))
			return is_cold_node(fio->page) ? CURSEG_WARM_NODE :
						CURSEG_HOT_NODE;
		return CURSEG_COLD_NODE;
	}
}
