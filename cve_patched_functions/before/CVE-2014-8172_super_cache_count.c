static unsigned long super_cache_count(struct shrinker *shrink,
				       struct shrink_control *sc)
{
	struct super_block *sb;
	long	total_objects = 0;

	sb = container_of(shrink, struct super_block, s_shrink);

	if (!grab_super_passive(sb))
		return 0;

	if (sb->s_op && sb->s_op->nr_cached_objects)
		total_objects = sb->s_op->nr_cached_objects(sb,
						 sc->nid);

	total_objects += list_lru_count_node(&sb->s_dentry_lru,
						 sc->nid);
	total_objects += list_lru_count_node(&sb->s_inode_lru,
						 sc->nid);

	total_objects = vfs_pressure_ratio(total_objects);
	drop_super(sb);
	return total_objects;
}
