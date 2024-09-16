static bool op_attr_value_from_binary(void *attr, const void *data,
				      size_t data_len, size_t *offs)
{
	uint32_t *v = attr;

	return op_u32_from_binary_helper(v, data, data_len, offs);
}
