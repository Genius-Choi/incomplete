static TEE_Result op_attr_bignum_from_obj(void *attr, void *src_attr)
{
	struct bignum **bn = attr;
	struct bignum **src_bn = src_attr;

	crypto_bignum_copy(*bn, *src_bn);
	return TEE_SUCCESS;
}
