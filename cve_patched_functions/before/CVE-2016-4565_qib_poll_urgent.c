static unsigned int qib_poll_urgent(struct qib_ctxtdata *rcd,
				    struct file *fp,
				    struct poll_table_struct *pt)
{
	struct qib_devdata *dd = rcd->dd;
	unsigned pollflag;

	poll_wait(fp, &rcd->wait, pt);

	spin_lock_irq(&dd->uctxt_lock);
	if (rcd->urgent != rcd->urgent_poll) {
		pollflag = POLLIN | POLLRDNORM;
		rcd->urgent_poll = rcd->urgent;
	} else {
		pollflag = 0;
		set_bit(QIB_CTXT_WAITING_URG, &rcd->flag);
	}
	spin_unlock_irq(&dd->uctxt_lock);

	return pollflag;
}
