static unsigned int poll_next(struct file *fp,
			      struct poll_table_struct *pt)
{
	struct hfi1_filedata *fd = fp->private_data;
	struct hfi1_ctxtdata *uctxt = fd->uctxt;
	struct hfi1_devdata *dd = uctxt->dd;
	unsigned pollflag;

	poll_wait(fp, &uctxt->wait, pt);

	spin_lock_irq(&dd->uctxt_lock);
	if (hdrqempty(uctxt)) {
		set_bit(HFI1_CTXT_WAITING_RCV, &uctxt->event_flags);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_INTRAVAIL_ENB, uctxt->ctxt);
		pollflag = 0;
	} else {
		pollflag = POLLIN | POLLRDNORM;
	}
	spin_unlock_irq(&dd->uctxt_lock);

	return pollflag;
}
