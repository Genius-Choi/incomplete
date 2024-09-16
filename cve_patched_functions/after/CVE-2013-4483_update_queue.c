static int update_queue(struct sem_array *sma, int semnum, struct list_head *pt)
{
	struct sem_queue *q;
	struct list_head *walk;
	struct list_head *pending_list;
	int semop_completed = 0;

	if (semnum == -1)
		pending_list = &sma->sem_pending;
	else
		pending_list = &sma->sem_base[semnum].sem_pending;

again:
	walk = pending_list->next;
	while (walk != pending_list) {
		int error, restart;

		q = container_of(walk, struct sem_queue, list);
		walk = walk->next;

		/* If we are scanning the single sop, per-semaphore list of
		 * one semaphore and that semaphore is 0, then it is not
		 * necessary to scan the "alter" entries: simple increments
		 * that affect only one entry succeed immediately and cannot
		 * be in the  per semaphore pending queue, and decrements
		 * cannot be successful if the value is already 0.
		 */
		if (semnum != -1 && sma->sem_base[semnum].semval == 0 &&
				q->alter)
			break;

		error = try_atomic_semop(sma, q->sops, q->nsops,
					 q->undo, q->pid);

		/* Does q->sleeper still need to sleep? */
		if (error > 0)
			continue;

		unlink_queue(sma, q);

		if (error) {
			restart = 0;
		} else {
			semop_completed = 1;
			restart = check_restart(sma, q);
		}

		wake_up_sem_queue_prepare(pt, q, error);
		if (restart)
			goto again;
	}
	return semop_completed;
}
