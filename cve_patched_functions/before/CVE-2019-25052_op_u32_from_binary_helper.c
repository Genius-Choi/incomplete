static bool op_u32_from_binary_helper(uint32_t *v, const uint8_t *data,
				      size_t data_len, size_t *offs)
{
	uint32_t field;

	if (!data || (*offs + sizeof(field)) > data_len)
		return false;

	memcpy(&field, data + *offs, sizeof(field));
	*v = TEE_U32_FROM_BIG_ENDIAN(field);
	(*offs) += sizeof(field);
	return true;
}
