int crypto_check_attr_type(struct rtattr **tb, u32 type)
{
	struct crypto_attr_type *algt;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	if ((algt->type ^ type) & algt->mask)
		return -EINVAL;

	return 0;
}
