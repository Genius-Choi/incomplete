static loff_t ui_lseek(struct file *filp, loff_t offset, int whence)
{
	struct hfi1_devdata *dd = filp->private_data;

	return fixed_size_llseek(filp, offset, whence,
		(dd->kregend - dd->kregbase) + DC8051_DATA_MEM_SIZE);
}
