static inline int hugetlbfs_dec_free_inodes(struct hugetlbfs_sb_info *sbinfo)
{
	if (sbinfo->free_inodes >= 0) {
		spin_lock(&sbinfo->stat_lock);
		if (unlikely(!sbinfo->free_inodes)) {
			spin_unlock(&sbinfo->stat_lock);
			return 0;
		}
		sbinfo->free_inodes--;
		spin_unlock(&sbinfo->stat_lock);
	}

	return 1;
}
