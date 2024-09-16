static TEE_Result op_u32_to_binary_helper(uint32_t v, uint8_t *data,
				    size_t data_len, size_t *offs)
{
	uint32_t field;
	size_t next_offs;

	if (ADD_OVERFLOW(*offs, sizeof(field), &next_offs))
		return TEE_ERROR_OVERFLOW;

	if (data && next_offs <= data_len) {
		field = TEE_U32_TO_BIG_ENDIAN(v);
		memcpy(data + *offs, &field, sizeof(field));
	}
	(*offs) = next_offs;

	return TEE_SUCCESS;
}
