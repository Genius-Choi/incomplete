grub_ext2_read_file (grub_fshelp_node_t node,
     void (*read_hook) (grub_disk_addr_t sector,
		unsigned offset, unsigned length, void *closure),
     void *closure, int flags, int pos, grub_size_t len, char *buf)
{
	return grub_fshelp_read_file (node->data->disk, node, read_hook, closure,
		flags, pos, len, buf, grub_ext2_read_block,
		node->inode.size, LOG2_EXT2_BLOCK_SIZE (node->data));
}
