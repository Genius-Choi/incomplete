static void acquire_freeze_lock(struct super_block *sb, int level, bool trylock,
				unsigned long ip)
{
	int i;

	if (!trylock) {
		for (i = 0; i < level - 1; i++)
			if (lock_is_held(&sb->s_writers.lock_map[i])) {
				trylock = true;
				break;
			}
	}
	rwsem_acquire_read(&sb->s_writers.lock_map[level-1], 0, trylock, ip);
}
