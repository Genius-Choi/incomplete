static int ext4_bh_unmapped(handle_t *handle, struct buffer_head *bh)
{
	return !buffer_mapped(bh);
}
