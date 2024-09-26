static ssize_t ucma_process_join(struct ucma_file *file,
				 struct rdma_ucm_join_mcast *cmd,  int out_len)
{
	struct rdma_ucm_create_id_resp resp;
	struct ucma_context *ctx;
	struct ucma_multicast *mc;
	struct sockaddr *addr;
	int ret;

	if (out_len < sizeof(resp))
		return -ENOSPC;

	addr = (struct sockaddr *) &cmd->addr;
	if (cmd->reserved || !cmd->addr_size || (cmd->addr_size != rdma_addr_size(addr)))
		return -EINVAL;

	ctx = ucma_get_ctx(file, cmd->id);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	mutex_lock(&file->mut);
	mc = ucma_alloc_multicast(ctx);
	if (!mc) {
		ret = -ENOMEM;
		goto err1;
	}

	mc->uid = cmd->uid;
	memcpy(&mc->addr, addr, cmd->addr_size);
	ret = rdma_join_multicast(ctx->cm_id, (struct sockaddr *) &mc->addr, mc);
	if (ret)
		goto err2;

	resp.id = mc->id;
	if (copy_to_user((void __user *)(unsigned long) cmd->response,
			 &resp, sizeof(resp))) {
		ret = -EFAULT;
		goto err3;
	}

	mutex_unlock(&file->mut);
	ucma_put_ctx(ctx);
	return 0;

err3:
	rdma_leave_multicast(ctx->cm_id, (struct sockaddr *) &mc->addr);
	ucma_cleanup_mc_events(mc);
err2:
	mutex_lock(&mut);
	idr_remove(&multicast_idr, mc->id);
	mutex_unlock(&mut);
	list_del(&mc->list);
	kfree(mc);
err1:
	mutex_unlock(&file->mut);
	ucma_put_ctx(ctx);
	return ret;
}
