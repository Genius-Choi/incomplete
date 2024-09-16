void qib_dev_cleanup(void)
{
	if (qib_class) {
		class_destroy(qib_class);
		qib_class = NULL;
	}

	unregister_chrdev_region(qib_dev, QIB_NMINORS);
}
