void address_space_init_once(struct address_space *mapping)
{
	memset(mapping, 0, sizeof(*mapping));
	INIT_RADIX_TREE(&mapping->page_tree, GFP_ATOMIC);
	spin_lock_init(&mapping->tree_lock);
	mutex_init(&mapping->i_mmap_mutex);
	INIT_LIST_HEAD(&mapping->private_list);
	spin_lock_init(&mapping->private_lock);
	mapping->i_mmap = RB_ROOT;
	INIT_LIST_HEAD(&mapping->i_mmap_nonlinear);
}
