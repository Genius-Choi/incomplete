svc_create_pooled(struct svc_program *prog, unsigned int bufsize,
		  struct svc_serv_ops *ops)
{
	struct svc_serv *serv;
	unsigned int npools = svc_pool_map_get();

	serv = __svc_create(prog, bufsize, npools, ops);
	if (!serv)
		goto out_err;
	return serv;
out_err:
	svc_pool_map_put();
	return NULL;
}
