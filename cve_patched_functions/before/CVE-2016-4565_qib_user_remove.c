static void qib_user_remove(struct qib_devdata *dd)
{
	if (atomic_dec_return(&user_count) == 0)
		qib_cdev_cleanup(&wildcard_cdev, &wildcard_device);

	qib_cdev_cleanup(&dd->user_cdev, &dd->user_device);
}
