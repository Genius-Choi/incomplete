static inline void ss_add(struct msg_queue *msq, struct msg_sender *mss)
{
	mss->tsk = current;
	__set_current_state(TASK_INTERRUPTIBLE);
	list_add_tail(&mss->list, &msq->q_senders);
}
