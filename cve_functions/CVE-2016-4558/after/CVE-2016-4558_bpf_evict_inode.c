static void bpf_evict_inode(struct inode *inode)
{
	enum bpf_type type;

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);

	if (!bpf_inode_type(inode, &type))
		bpf_any_put(inode->i_private, type);
}
