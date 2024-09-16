rpc_setup_pipedir(struct rpc_clnt *clnt, char *dir_name)
{
	static uint32_t clntid;
	struct nameidata nd;
	struct path path;
	char name[15];
	struct qstr q = {
		.name = name,
	};
	int error;

	clnt->cl_path.mnt = ERR_PTR(-ENOENT);
	clnt->cl_path.dentry = ERR_PTR(-ENOENT);
	if (dir_name == NULL)
		return 0;

	path.mnt = rpc_get_mount();
	if (IS_ERR(path.mnt))
		return PTR_ERR(path.mnt);
	error = vfs_path_lookup(path.mnt->mnt_root, path.mnt, dir_name, 0, &nd);
	if (error)
		goto err;

	for (;;) {
		q.len = snprintf(name, sizeof(name), "clnt%x", (unsigned int)clntid++);
		name[sizeof(name) - 1] = '\0';
		q.hash = full_name_hash(q.name, q.len);
		path.dentry = rpc_create_client_dir(nd.path.dentry, &q, clnt);
		if (!IS_ERR(path.dentry))
			break;
		error = PTR_ERR(path.dentry);
		if (error != -EEXIST) {
			printk(KERN_INFO "RPC: Couldn't create pipefs entry"
					" %s/%s, error %d\n",
					dir_name, name, error);
			goto err_path_put;
		}
	}
	path_put(&nd.path);
	clnt->cl_path = path;
	return 0;
err_path_put:
	path_put(&nd.path);
err:
	rpc_put_mount();
	return error;
}
