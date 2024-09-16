static void airo_handle_cisco_mic(struct airo_info *ai)
{
	if (test_bit(FLAG_MIC_CAPABLE, &ai->flags)) {
		set_bit(JOB_MIC, &ai->jobs);
		wake_up_interruptible(&ai->thr_wait);
	}
}
