static void key_search_validate(struct extent_buffer *b,
				struct btrfs_key *key,
				int level)
{
#ifdef CONFIG_BTRFS_ASSERT
	struct btrfs_disk_key disk_key;

	btrfs_cpu_key_to_disk(&disk_key, key);

	if (level == 0)
		ASSERT(!memcmp_extent_buffer(b, &disk_key,
		    offsetof(struct btrfs_leaf, items[0].key),
		    sizeof(disk_key)));
	else
		ASSERT(!memcmp_extent_buffer(b, &disk_key,
		    offsetof(struct btrfs_node, ptrs[0].key),
		    sizeof(disk_key)));
#endif
}
