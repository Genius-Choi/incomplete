int f2fs_issue_flush(struct f2fs_sb_info *sbi)
{
	struct flush_cmd_control *fcc = SM_I(sbi)->fcc_info;
	struct flush_cmd cmd;
	int ret;

	if (test_opt(sbi, NOBARRIER))
		return 0;

	if (!test_opt(sbi, FLUSH_MERGE)) {
		ret = submit_flush_wait(sbi);
		atomic_inc(&fcc->issued_flush);
		return ret;
	}

	if (!atomic_read(&fcc->issing_flush)) {
		atomic_inc(&fcc->issing_flush);
		ret = submit_flush_wait(sbi);
		atomic_dec(&fcc->issing_flush);

		atomic_inc(&fcc->issued_flush);
		return ret;
	}

	init_completion(&cmd.wait);

	atomic_inc(&fcc->issing_flush);
	llist_add(&cmd.llnode, &fcc->issue_list);

	if (!fcc->dispatch_list)
		wake_up(&fcc->flush_wait_queue);

	if (fcc->f2fs_issue_flush) {
		wait_for_completion(&cmd.wait);
		atomic_dec(&fcc->issing_flush);
	} else {
		llist_del_all(&fcc->issue_list);
		atomic_set(&fcc->issing_flush, 0);
	}

	return cmd.ret;
}
