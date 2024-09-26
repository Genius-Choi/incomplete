param_set_pool_mode(const char *val, struct kernel_param *kp)
{
	int *ip = (int *)kp->arg;
	struct svc_pool_map *m = &svc_pool_map;
	int err;

	mutex_lock(&svc_pool_map_mutex);

	err = -EBUSY;
	if (m->count)
		goto out;

	err = 0;
	if (!strncmp(val, "auto", 4))
		*ip = SVC_POOL_AUTO;
	else if (!strncmp(val, "global", 6))
		*ip = SVC_POOL_GLOBAL;
	else if (!strncmp(val, "percpu", 6))
		*ip = SVC_POOL_PERCPU;
	else if (!strncmp(val, "pernode", 7))
		*ip = SVC_POOL_PERNODE;
	else
		err = -EINVAL;

out:
	mutex_unlock(&svc_pool_map_mutex);
	return err;
}
