static void op_attr_bignum_clear(void *attr)
{
	struct bignum **bn = attr;

	crypto_bignum_clear(*bn);
}
