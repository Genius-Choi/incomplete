static int cmd_attr_register_cpumask(struct genl_info *info)
{
	cpumask_var_t mask;
	int rc;

	if (!alloc_cpumask_var(&mask, GFP_KERNEL))
		return -ENOMEM;
	rc = parse(info->attrs[TASKSTATS_CMD_ATTR_REGISTER_CPUMASK], mask);
	if (rc < 0)
		goto out;
	rc = add_del_listener(info->snd_pid, mask, REGISTER);
out:
	free_cpumask_var(mask);
	return rc;
}
