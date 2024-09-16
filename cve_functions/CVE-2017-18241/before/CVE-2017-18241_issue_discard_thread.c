static int issue_discard_thread(void *data)
{
	struct f2fs_sb_info *sbi = data;
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	wait_queue_head_t *q = &dcc->discard_wait_queue;

	set_freezable();

	do {
		wait_event_interruptible(*q, kthread_should_stop() ||
					freezing(current) ||
					atomic_read(&dcc->discard_cmd_cnt));
		if (try_to_freeze())
			continue;
		if (kthread_should_stop())
			return 0;

		__issue_discard_cmd(sbi, true);
		__wait_discard_cmd(sbi, true);

		congestion_wait(BLK_RW_SYNC, HZ/50);
	} while (!kthread_should_stop());
	return 0;
}
