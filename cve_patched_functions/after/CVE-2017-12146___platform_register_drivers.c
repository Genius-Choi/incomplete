int __platform_register_drivers(struct platform_driver * const *drivers,
				unsigned int count, struct module *owner)
{
	unsigned int i;
	int err;

	for (i = 0; i < count; i++) {
		pr_debug("registering platform driver %ps\n", drivers[i]);

		err = __platform_driver_register(drivers[i], owner);
		if (err < 0) {
			pr_err("failed to register platform driver %ps: %d\n",
			       drivers[i], err);
			goto error;
		}
	}

	return 0;

error:
	while (i--) {
		pr_debug("unregistering platform driver %ps\n", drivers[i]);
		platform_driver_unregister(drivers[i]);
	}

	return err;
}
