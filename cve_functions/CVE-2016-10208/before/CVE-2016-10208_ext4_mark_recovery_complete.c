static void ext4_mark_recovery_complete(struct super_block *sb,
					struct ext4_super_block *es)
{
	journal_t *journal = EXT4_SB(sb)->s_journal;

	if (!ext4_has_feature_journal(sb)) {
		BUG_ON(journal != NULL);
		return;
	}
	jbd2_journal_lock_updates(journal);
	if (jbd2_journal_flush(journal) < 0)
		goto out;

	if (ext4_has_feature_journal_needs_recovery(sb) &&
	    sb->s_flags & MS_RDONLY) {
		ext4_clear_feature_journal_needs_recovery(sb);
		ext4_commit_super(sb, 1);
	}

out:
	jbd2_journal_unlock_updates(journal);
}
