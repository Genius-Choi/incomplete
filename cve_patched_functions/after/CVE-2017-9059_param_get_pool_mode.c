param_get_pool_mode(char *buf, struct kernel_param *kp)
{
	int *ip = (int *)kp->arg;

	switch (*ip)
	{
	case SVC_POOL_AUTO:
		return strlcpy(buf, "auto", 20);
	case SVC_POOL_GLOBAL:
		return strlcpy(buf, "global", 20);
	case SVC_POOL_PERCPU:
		return strlcpy(buf, "percpu", 20);
	case SVC_POOL_PERNODE:
		return strlcpy(buf, "pernode", 20);
	default:
		return sprintf(buf, "%d", *ip);
	}
}
