static bool op_attr_bignum_from_binary(void *attr, const void *data,
				       size_t data_len, size_t *offs)
{
	struct bignum **bn = attr;
	uint32_t n;

	if (!op_u32_from_binary_helper(&n, data, data_len, offs))
		return false;

	if ((*offs + n) > data_len)
		return false;
	if (crypto_bignum_bin2bn((const uint8_t *)data + *offs, n, *bn))
		return false;
	(*offs) += n;
	return true;
}
