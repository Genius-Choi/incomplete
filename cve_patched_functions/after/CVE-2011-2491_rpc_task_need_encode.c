rpc_task_need_encode(struct rpc_task *task)
{
	return task->tk_rqstp->rq_snd_buf.len == 0;
}
