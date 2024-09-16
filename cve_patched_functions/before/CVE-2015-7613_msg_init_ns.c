void msg_init_ns(struct ipc_namespace *ns)
{
	ns->msg_ctlmax = MSGMAX;
	ns->msg_ctlmnb = MSGMNB;
	ns->msg_ctlmni = MSGMNI;

	atomic_set(&ns->msg_bytes, 0);
	atomic_set(&ns->msg_hdrs, 0);
	ipc_init_ids(&ns->ids[IPC_MSG_IDS]);
}
