static int nfs_idmap_legacy_upcall(struct key_construction *cons,
				   const char *op,
				   void *aux)
{
	struct idmap_legacy_upcalldata *data;
	struct rpc_pipe_msg *msg;
	struct idmap_msg *im;
	struct idmap *idmap = (struct idmap *)aux;
	struct key *key = cons->key;
	int ret = -ENOMEM;

	/* msg and im are freed in idmap_pipe_destroy_msg */
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		goto out1;

	msg = &data->pipe_msg;
	im = &data->idmap_msg;
	data->idmap = idmap;
	data->key_cons = cons;

	ret = nfs_idmap_prepare_message(key->description, idmap, im, msg);
	if (ret < 0)
		goto out2;

	ret = -EAGAIN;
	if (!nfs_idmap_prepare_pipe_upcall(idmap, data))
		goto out2;

	ret = rpc_queue_upcall(idmap->idmap_pipe, msg);
	if (ret < 0)
		nfs_idmap_abort_pipe_upcall(idmap, ret);

	return ret;
out2:
	kfree(data);
out1:
	complete_request_key(cons, ret);
	return ret;
}
