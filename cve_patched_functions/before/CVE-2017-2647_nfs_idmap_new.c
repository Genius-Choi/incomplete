nfs_idmap_new(struct nfs_client *clp)
{
	struct idmap *idmap;
	struct rpc_pipe *pipe;
	int error;

	idmap = kzalloc(sizeof(*idmap), GFP_KERNEL);
	if (idmap == NULL)
		return -ENOMEM;

	rpc_init_pipe_dir_object(&idmap->idmap_pdo,
			&nfs_idmap_pipe_dir_object_ops,
			idmap);

	pipe = rpc_mkpipe_data(&idmap_upcall_ops, 0);
	if (IS_ERR(pipe)) {
		error = PTR_ERR(pipe);
		goto err;
	}
	idmap->idmap_pipe = pipe;
	mutex_init(&idmap->idmap_mutex);

	error = rpc_add_pipe_dir_object(clp->cl_net,
			&clp->cl_rpcclient->cl_pipedir_objects,
			&idmap->idmap_pdo);
	if (error)
		goto err_destroy_pipe;

	clp->cl_idmap = idmap;
	return 0;
err_destroy_pipe:
	rpc_destroy_pipe_data(idmap->idmap_pipe);
err:
	kfree(idmap);
	return error;
}
