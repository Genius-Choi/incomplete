long prune_icache_sb(struct super_block *sb, unsigned long nr_to_scan,
		     int nid)
{
	LIST_HEAD(freeable);
	long freed;

	freed = list_lru_walk_node(&sb->s_inode_lru, nid, inode_lru_isolate,
				       &freeable, &nr_to_scan);
	dispose_list(&freeable);
	return freed;
}
