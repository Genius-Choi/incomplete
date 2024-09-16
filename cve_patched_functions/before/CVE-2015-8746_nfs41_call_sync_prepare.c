static void nfs41_call_sync_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs4_call_sync_data *data = calldata;
	struct nfs4_session *session = nfs4_get_session(data->seq_server);

	dprintk("--> %s data->seq_server %p\n", __func__, data->seq_server);

	nfs41_setup_sequence(session, data->seq_args, data->seq_res, task);
}
