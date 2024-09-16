static struct usb_function_instance *ffs_alloc_inst(void)
{
	struct f_fs_opts *opts;
	struct ffs_dev *dev;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);

	opts->func_inst.set_inst_name = ffs_set_inst_name;
	opts->func_inst.free_func_inst = ffs_free_inst;
	ffs_dev_lock();
	dev = _ffs_alloc_dev();
	ffs_dev_unlock();
	if (IS_ERR(dev)) {
		kfree(opts);
		return ERR_CAST(dev);
	}
	opts->dev = dev;
	dev->opts = opts;

	config_group_init_type_name(&opts->func_inst.group, "",
				    &ffs_func_type);
	return &opts->func_inst;
}
