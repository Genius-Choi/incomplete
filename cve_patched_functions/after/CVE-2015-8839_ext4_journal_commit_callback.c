static void ext4_journal_commit_callback(journal_t *journal, transaction_t *txn)
{
	struct super_block		*sb = journal->j_private;
	struct ext4_sb_info		*sbi = EXT4_SB(sb);
	int				error = is_journal_aborted(journal);
	struct ext4_journal_cb_entry	*jce;

	BUG_ON(txn->t_state == T_FINISHED);
	spin_lock(&sbi->s_md_lock);
	while (!list_empty(&txn->t_private_list)) {
		jce = list_entry(txn->t_private_list.next,
				 struct ext4_journal_cb_entry, jce_list);
		list_del_init(&jce->jce_list);
		spin_unlock(&sbi->s_md_lock);
		jce->jce_func(sb, jce, error);
		spin_lock(&sbi->s_md_lock);
	}
	spin_unlock(&sbi->s_md_lock);
}
