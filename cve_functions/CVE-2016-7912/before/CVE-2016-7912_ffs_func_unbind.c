static void ffs_func_unbind(struct usb_configuration *c,
			    struct usb_function *f)
{
	struct ffs_function *func = ffs_func_from_usb(f);
	struct ffs_data *ffs = func->ffs;
	struct f_fs_opts *opts =
		container_of(f->fi, struct f_fs_opts, func_inst);
	struct ffs_ep *ep = func->eps;
	unsigned count = ffs->eps_count;
	unsigned long flags;

	ENTER();
	if (ffs->func == func) {
		ffs_func_eps_disable(func);
		ffs->func = NULL;
	}

	if (!--opts->refcnt)
		functionfs_unbind(ffs);

	/* cleanup after autoconfig */
	spin_lock_irqsave(&func->ffs->eps_lock, flags);
	do {
		if (ep->ep && ep->req)
			usb_ep_free_request(ep->ep, ep->req);
		ep->req = NULL;
		++ep;
	} while (--count);
	spin_unlock_irqrestore(&func->ffs->eps_lock, flags);
	kfree(func->eps);
	func->eps = NULL;
	/*
	 * eps, descriptors and interfaces_nums are allocated in the
	 * same chunk so only one free is required.
	 */
	func->function.fs_descriptors = NULL;
	func->function.hs_descriptors = NULL;
	func->function.ss_descriptors = NULL;
	func->interfaces_nums = NULL;

	ffs_event_add(ffs, FUNCTIONFS_UNBIND);
}
