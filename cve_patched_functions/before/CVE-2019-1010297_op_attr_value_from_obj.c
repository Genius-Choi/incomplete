static TEE_Result op_attr_value_from_obj(void *attr, void *src_attr)
{
	uint32_t *v = attr;
	uint32_t *src_v = src_attr;

	*v = *src_v;
	return TEE_SUCCESS;
}
