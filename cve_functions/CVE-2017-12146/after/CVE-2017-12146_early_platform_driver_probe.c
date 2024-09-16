int __init early_platform_driver_probe(char *class_str,
				       int nr_probe,
				       int user_only)
{
	int k, n, i;

	n = 0;
	for (i = -2; n < nr_probe; i++) {
		k = early_platform_driver_probe_id(class_str, i, nr_probe - n);

		if (k < 0)
			break;

		n += k;

		if (user_only)
			break;
	}

	return n;
}
