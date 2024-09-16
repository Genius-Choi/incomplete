xt_register_matches(struct xt_match *match, unsigned int n)
{
	unsigned int i;
	int err = 0;

	for (i = 0; i < n; i++) {
		err = xt_register_match(&match[i]);
		if (err)
			goto err;
	}
	return err;

err:
	if (i > 0)
		xt_unregister_matches(match, i);
	return err;
}
