static inline void check_dl_overrun(struct task_struct *tsk)
{
	if (tsk->dl.dl_overrun) {
		tsk->dl.dl_overrun = 0;
		__group_send_sig_info(SIGXCPU, SEND_SIG_PRIV, tsk);
	}
}
