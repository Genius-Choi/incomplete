static void ffs_func_eps_disable(struct ffs_function *func)
{
	struct ffs_ep *ep         = func->eps;
	struct ffs_epfile *epfile = func->ffs->epfiles;
	unsigned count            = func->ffs->eps_count;
	unsigned long flags;

	spin_lock_irqsave(&func->ffs->eps_lock, flags);
	do {
		/* pending requests get nuked */
		if (likely(ep->ep))
			usb_ep_disable(ep->ep);
		++ep;

		if (epfile) {
			epfile->ep = NULL;
			++epfile;
		}
	} while (--count);
	spin_unlock_irqrestore(&func->ffs->eps_lock, flags);
}
