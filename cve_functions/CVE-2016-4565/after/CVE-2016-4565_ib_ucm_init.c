static int __init ib_ucm_init(void)
{
	int ret;

	ret = register_chrdev_region(IB_UCM_BASE_DEV, IB_UCM_MAX_DEVICES,
				     "infiniband_cm");
	if (ret) {
		pr_err("ucm: couldn't register device number\n");
		goto error1;
	}

	ret = class_create_file(&cm_class, &class_attr_abi_version.attr);
	if (ret) {
		pr_err("ucm: couldn't create abi_version attribute\n");
		goto error2;
	}

	ret = ib_register_client(&ucm_client);
	if (ret) {
		pr_err("ucm: couldn't register client\n");
		goto error3;
	}
	return 0;

error3:
	class_remove_file(&cm_class, &class_attr_abi_version.attr);
error2:
	unregister_chrdev_region(IB_UCM_BASE_DEV, IB_UCM_MAX_DEVICES);
error1:
	return ret;
}
