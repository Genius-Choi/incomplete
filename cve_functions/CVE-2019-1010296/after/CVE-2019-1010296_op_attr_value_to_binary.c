static TEE_Result op_attr_value_to_binary(void *attr, void *data,
					  size_t data_len, size_t *offs)
{
	uint32_t *v = attr;

	return op_u32_to_binary_helper(*v, data, data_len, offs);
}
