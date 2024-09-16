static void user_remove(struct hfi1_devdata *dd)
{
	if (atomic_dec_return(&user_count) == 0)
		hfi1_cdev_cleanup(&wildcard_cdev, &wildcard_device);

	hfi1_cdev_cleanup(&dd->user_cdev, &dd->user_device);
	hfi1_cdev_cleanup(&dd->ui_cdev, &dd->ui_device);
}
