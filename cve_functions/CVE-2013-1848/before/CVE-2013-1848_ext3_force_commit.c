int ext3_force_commit(struct super_block *sb)
{
	journal_t *journal;
	int ret;

	if (sb->s_flags & MS_RDONLY)
		return 0;

	journal = EXT3_SB(sb)->s_journal;
	ret = ext3_journal_force_commit(journal);
	return ret;
}
