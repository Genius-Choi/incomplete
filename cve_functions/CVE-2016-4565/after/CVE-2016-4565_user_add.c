static int user_add(struct hfi1_devdata *dd)
{
	char name[10];
	int ret;

	if (atomic_inc_return(&user_count) == 1) {
		ret = hfi1_cdev_init(0, class_name(), &hfi1_file_ops,
				     &wildcard_cdev, &wildcard_device,
				     true);
		if (ret)
			goto done;
	}

	snprintf(name, sizeof(name), "%s_%d", class_name(), dd->unit);
	ret = hfi1_cdev_init(dd->unit + 1, name, &hfi1_file_ops,
			     &dd->user_cdev, &dd->user_device,
			     true);
	if (ret)
		goto done;

	if (create_ui) {
		snprintf(name, sizeof(name),
			 "%s_ui%d", class_name(), dd->unit);
		ret = hfi1_cdev_init(dd->unit + UI_OFFSET, name, &ui_file_ops,
				     &dd->ui_cdev, &dd->ui_device,
				     false);
		if (ret)
			goto done;
	}

	return 0;
done:
	user_remove(dd);
	return ret;
}
