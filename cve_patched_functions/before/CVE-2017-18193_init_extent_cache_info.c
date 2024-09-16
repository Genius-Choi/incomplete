void init_extent_cache_info(struct f2fs_sb_info *sbi)
{
	INIT_RADIX_TREE(&sbi->extent_tree_root, GFP_NOIO);
	mutex_init(&sbi->extent_tree_lock);
	INIT_LIST_HEAD(&sbi->extent_list);
	spin_lock_init(&sbi->extent_lock);
	atomic_set(&sbi->total_ext_tree, 0);
	INIT_LIST_HEAD(&sbi->zombie_list);
	atomic_set(&sbi->total_zombie_tree, 0);
	atomic_set(&sbi->total_ext_node, 0);
}
