int __init qib_dev_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&qib_dev, 0, QIB_NMINORS, QIB_DRV_NAME);
	if (ret < 0) {
		pr_err("Could not allocate chrdev region (err %d)\n", -ret);
		goto done;
	}

	qib_class = class_create(THIS_MODULE, "ipath");
	if (IS_ERR(qib_class)) {
		ret = PTR_ERR(qib_class);
		pr_err("Could not create device class (err %d)\n", -ret);
		unregister_chrdev_region(qib_dev, QIB_NMINORS);
	}

done:
	return ret;
}
