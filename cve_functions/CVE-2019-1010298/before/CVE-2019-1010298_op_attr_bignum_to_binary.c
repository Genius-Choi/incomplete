static TEE_Result op_attr_bignum_to_binary(void *attr, void *data,
					   size_t data_len, size_t *offs)
{
	TEE_Result res;
	struct bignum **bn = attr;
	uint32_t n = crypto_bignum_num_bytes(*bn);
	size_t next_offs;

	res = op_u32_to_binary_helper(n, data, data_len, offs);
	if (res != TEE_SUCCESS)
		return res;

	if (ADD_OVERFLOW(*offs, n, &next_offs))
		return TEE_ERROR_OVERFLOW;

	if (data && next_offs <= data_len)
		crypto_bignum_bn2bin(*bn, (uint8_t *)data + *offs);
	(*offs) = next_offs;

	return TEE_SUCCESS;
}
