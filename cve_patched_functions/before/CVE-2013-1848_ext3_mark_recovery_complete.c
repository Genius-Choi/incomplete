static void ext3_mark_recovery_complete(struct super_block * sb,
					struct ext3_super_block * es)
{
	journal_t *journal = EXT3_SB(sb)->s_journal;

	journal_lock_updates(journal);
	if (journal_flush(journal) < 0)
		goto out;

	if (EXT3_HAS_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_RECOVER) &&
	    sb->s_flags & MS_RDONLY) {
		EXT3_CLEAR_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_RECOVER);
		ext3_commit_super(sb, es, 1);
	}

out:
	journal_unlock_updates(journal);
}
