static int __init taskstats_init(void)
{
	int rc;

	rc = genl_register_family(&family);
	if (rc)
		return rc;

	rc = genl_register_ops(&family, &taskstats_ops);
	if (rc < 0)
		goto err;

	rc = genl_register_ops(&family, &cgroupstats_ops);
	if (rc < 0)
		goto err_cgroup_ops;

	family_registered = 1;
	pr_info("registered taskstats version %d\n", TASKSTATS_GENL_VERSION);
	return 0;
err_cgroup_ops:
	genl_unregister_ops(&family, &taskstats_ops);
err:
	genl_unregister_family(&family);
	return rc;
}
