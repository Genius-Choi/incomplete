void hfi1_device_remove(struct hfi1_devdata *dd)
{
	user_remove(dd);
	hfi1_diag_remove(dd);
}
