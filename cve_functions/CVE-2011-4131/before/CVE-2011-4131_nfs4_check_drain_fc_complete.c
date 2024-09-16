static void nfs4_check_drain_fc_complete(struct nfs4_session *ses)
{
	struct rpc_task *task;

	if (!test_bit(NFS4_SESSION_DRAINING, &ses->session_state)) {
		task = rpc_wake_up_next(&ses->fc_slot_table.slot_tbl_waitq);
		if (task)
			rpc_task_set_priority(task, RPC_PRIORITY_PRIVILEGED);
		return;
	}

	if (ses->fc_slot_table.highest_used_slotid != -1)
		return;

	dprintk("%s COMPLETE: Session Fore Channel Drained\n", __func__);
	complete(&ses->fc_slot_table.complete);
}
