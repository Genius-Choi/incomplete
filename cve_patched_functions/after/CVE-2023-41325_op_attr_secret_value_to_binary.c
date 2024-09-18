static TEE_Result op_attr_secret_value_to_binary(void *attr, void *data,
					   size_t data_len, size_t *offs)
{
	TEE_Result res;
	struct tee_cryp_obj_secret *key = attr;
	size_t next_offs;

	res = op_u32_to_binary_helper(key->key_size, data, data_len, offs);
	if (res != TEE_SUCCESS)
		return res;

	if (ADD_OVERFLOW(*offs, key->key_size, &next_offs))
		return TEE_ERROR_OVERFLOW;

	if (data && next_offs <= data_len)
		memcpy((uint8_t *)data + *offs, key + 1, key->key_size);
	(*offs) = next_offs;

	return TEE_SUCCESS;
}
