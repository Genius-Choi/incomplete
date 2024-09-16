int qib_device_create(struct qib_devdata *dd)
{
	int r, ret;

	r = qib_user_add(dd);
	ret = qib_diag_add(dd);
	if (r && !ret)
		ret = r;
	return ret;
}
