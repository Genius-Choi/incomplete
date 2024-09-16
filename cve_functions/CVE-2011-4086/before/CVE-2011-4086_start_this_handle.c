static int start_this_handle(journal_t *journal, handle_t *handle,
			     gfp_t gfp_mask)
{
	transaction_t	*transaction, *new_transaction = NULL;
	tid_t		tid;
	int		needed, need_to_start;
	int		nblocks = handle->h_buffer_credits;
	unsigned long ts = jiffies;

	if (nblocks > journal->j_max_transaction_buffers) {
		printk(KERN_ERR "JBD2: %s wants too many credits (%d > %d)\n",
		       current->comm, nblocks,
		       journal->j_max_transaction_buffers);
		return -ENOSPC;
	}

alloc_transaction:
	if (!journal->j_running_transaction) {
		new_transaction = kzalloc(sizeof(*new_transaction), gfp_mask);
		if (!new_transaction) {
			/*
			 * If __GFP_FS is not present, then we may be
			 * being called from inside the fs writeback
			 * layer, so we MUST NOT fail.  Since
			 * __GFP_NOFAIL is going away, we will arrange
			 * to retry the allocation ourselves.
			 */
			if ((gfp_mask & __GFP_FS) == 0) {
				congestion_wait(BLK_RW_ASYNC, HZ/50);
				goto alloc_transaction;
			}
			return -ENOMEM;
		}
	}

	jbd_debug(3, "New handle %p going live.\n", handle);

	/*
	 * We need to hold j_state_lock until t_updates has been incremented,
	 * for proper journal barrier handling
	 */
repeat:
	read_lock(&journal->j_state_lock);
	BUG_ON(journal->j_flags & JBD2_UNMOUNT);
	if (is_journal_aborted(journal) ||
	    (journal->j_errno != 0 && !(journal->j_flags & JBD2_ACK_ERR))) {
		read_unlock(&journal->j_state_lock);
		kfree(new_transaction);
		return -EROFS;
	}

	/* Wait on the journal's transaction barrier if necessary */
	if (journal->j_barrier_count) {
		read_unlock(&journal->j_state_lock);
		wait_event(journal->j_wait_transaction_locked,
				journal->j_barrier_count == 0);
		goto repeat;
	}

	if (!journal->j_running_transaction) {
		read_unlock(&journal->j_state_lock);
		if (!new_transaction)
			goto alloc_transaction;
		write_lock(&journal->j_state_lock);
		if (!journal->j_running_transaction) {
			jbd2_get_transaction(journal, new_transaction);
			new_transaction = NULL;
		}
		write_unlock(&journal->j_state_lock);
		goto repeat;
	}

	transaction = journal->j_running_transaction;

	/*
	 * If the current transaction is locked down for commit, wait for the
	 * lock to be released.
	 */
	if (transaction->t_state == T_LOCKED) {
		DEFINE_WAIT(wait);

		prepare_to_wait(&journal->j_wait_transaction_locked,
					&wait, TASK_UNINTERRUPTIBLE);
		read_unlock(&journal->j_state_lock);
		schedule();
		finish_wait(&journal->j_wait_transaction_locked, &wait);
		goto repeat;
	}

	/*
	 * If there is not enough space left in the log to write all potential
	 * buffers requested by this operation, we need to stall pending a log
	 * checkpoint to free some more log space.
	 */
	needed = atomic_add_return(nblocks,
				   &transaction->t_outstanding_credits);

	if (needed > journal->j_max_transaction_buffers) {
		/*
		 * If the current transaction is already too large, then start
		 * to commit it: we can then go back and attach this handle to
		 * a new transaction.
		 */
		DEFINE_WAIT(wait);

		jbd_debug(2, "Handle %p starting new commit...\n", handle);
		atomic_sub(nblocks, &transaction->t_outstanding_credits);
		prepare_to_wait(&journal->j_wait_transaction_locked, &wait,
				TASK_UNINTERRUPTIBLE);
		tid = transaction->t_tid;
		need_to_start = !tid_geq(journal->j_commit_request, tid);
		read_unlock(&journal->j_state_lock);
		if (need_to_start)
			jbd2_log_start_commit(journal, tid);
		schedule();
		finish_wait(&journal->j_wait_transaction_locked, &wait);
		goto repeat;
	}

	/*
	 * The commit code assumes that it can get enough log space
	 * without forcing a checkpoint.  This is *critical* for
	 * correctness: a checkpoint of a buffer which is also
	 * associated with a committing transaction creates a deadlock,
	 * so commit simply cannot force through checkpoints.
	 *
	 * We must therefore ensure the necessary space in the journal
	 * *before* starting to dirty potentially checkpointed buffers
	 * in the new transaction.
	 *
	 * The worst part is, any transaction currently committing can
	 * reduce the free space arbitrarily.  Be careful to account for
	 * those buffers when checkpointing.
	 */

	/*
	 * @@@ AKPM: This seems rather over-defensive.  We're giving commit
	 * a _lot_ of headroom: 1/4 of the journal plus the size of
	 * the committing transaction.  Really, we only need to give it
	 * committing_transaction->t_outstanding_credits plus "enough" for
	 * the log control blocks.
	 * Also, this test is inconsistent with the matching one in
	 * jbd2_journal_extend().
	 */
	if (__jbd2_log_space_left(journal) < jbd_space_needed(journal)) {
		jbd_debug(2, "Handle %p waiting for checkpoint...\n", handle);
		atomic_sub(nblocks, &transaction->t_outstanding_credits);
		read_unlock(&journal->j_state_lock);
		write_lock(&journal->j_state_lock);
		if (__jbd2_log_space_left(journal) < jbd_space_needed(journal))
			__jbd2_log_wait_for_space(journal);
		write_unlock(&journal->j_state_lock);
		goto repeat;
	}

	/* OK, account for the buffers that this operation expects to
	 * use and add the handle to the running transaction. 
	 */
	update_t_max_wait(transaction, ts);
	handle->h_transaction = transaction;
	atomic_inc(&transaction->t_updates);
	atomic_inc(&transaction->t_handle_count);
	jbd_debug(4, "Handle %p given %d credits (total %d, free %d)\n",
		  handle, nblocks,
		  atomic_read(&transaction->t_outstanding_credits),
		  __jbd2_log_space_left(journal));
	read_unlock(&journal->j_state_lock);

	lock_map_acquire(&handle->h_lockdep_map);
	kfree(new_transaction);
	return 0;
}
