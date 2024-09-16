static void __issue_discard_cmd(struct f2fs_sb_info *sbi, bool issue_cond)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	struct list_head *pend_list;
	struct discard_cmd *dc, *tmp;
	struct blk_plug plug;
	int i, iter = 0;

	mutex_lock(&dcc->cmd_lock);
	f2fs_bug_on(sbi,
		!__check_rb_tree_consistence(sbi, &dcc->root));
	blk_start_plug(&plug);
	for (i = MAX_PLIST_NUM - 1; i >= 0; i--) {
		pend_list = &dcc->pend_list[i];
		list_for_each_entry_safe(dc, tmp, pend_list, list) {
			f2fs_bug_on(sbi, dc->state != D_PREP);

			if (!issue_cond || is_idle(sbi))
				__submit_discard_cmd(sbi, dc);
			if (issue_cond && iter++ > DISCARD_ISSUE_RATE)
				goto out;
		}
	}
out:
	blk_finish_plug(&plug);
	mutex_unlock(&dcc->cmd_lock);
}
