static unsigned int hfi1_poll(struct file *fp, struct poll_table_struct *pt)
{
	struct hfi1_ctxtdata *uctxt;
	unsigned pollflag;

	uctxt = ((struct hfi1_filedata *)fp->private_data)->uctxt;
	if (!uctxt)
		pollflag = POLLERR;
	else if (uctxt->poll_type == HFI1_POLL_TYPE_URGENT)
		pollflag = poll_urgent(fp, pt);
	else  if (uctxt->poll_type == HFI1_POLL_TYPE_ANYRCV)
		pollflag = poll_next(fp, pt);
	else /* invalid */
		pollflag = POLLERR;

	return pollflag;
}
