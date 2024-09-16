static int __init init_o2nm(void)
{
	int ret = -1;

	ret = o2hb_init();
	if (ret)
		goto out;

	ret = o2net_init();
	if (ret)
		goto out_o2hb;

	ret = o2net_register_hb_callbacks();
	if (ret)
		goto out_o2net;

	config_group_init(&o2nm_cluster_group.cs_subsys.su_group);
	mutex_init(&o2nm_cluster_group.cs_subsys.su_mutex);
	ret = configfs_register_subsystem(&o2nm_cluster_group.cs_subsys);
	if (ret) {
		printk(KERN_ERR "nodemanager: Registration returned %d\n", ret);
		goto out_callbacks;
	}

	ret = o2cb_sys_init();
	if (!ret)
		goto out;

	configfs_unregister_subsystem(&o2nm_cluster_group.cs_subsys);
out_callbacks:
	o2net_unregister_hb_callbacks();
out_o2net:
	o2net_exit();
out_o2hb:
	o2hb_exit();
out:
	return ret;
}
