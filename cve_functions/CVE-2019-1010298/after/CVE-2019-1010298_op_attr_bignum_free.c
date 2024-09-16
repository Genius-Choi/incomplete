static void op_attr_bignum_free(void *attr)
{
	struct bignum **bn = attr;

	crypto_bignum_free(*bn);
	*bn = NULL;
}
