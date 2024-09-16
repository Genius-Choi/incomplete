int hfi1_device_create(struct hfi1_devdata *dd)
{
	int r, ret;

	r = user_add(dd);
	ret = hfi1_diag_add(dd);
	if (r && !ret)
		ret = r;
	return ret;
}
