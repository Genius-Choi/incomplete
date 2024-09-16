static long ffs_ep0_ioctl(struct file *file, unsigned code, unsigned long value)
{
	struct ffs_data *ffs = file->private_data;
	struct usb_gadget *gadget = ffs->gadget;
	long ret;

	ENTER();

	if (code == FUNCTIONFS_INTERFACE_REVMAP) {
		struct ffs_function *func = ffs->func;
		ret = func ? ffs_func_revmap_intf(func, value) : -ENODEV;
	} else if (gadget && gadget->ops->ioctl) {
		ret = gadget->ops->ioctl(gadget, code, value);
	} else {
		ret = -ENOTTY;
	}

	return ret;
}
