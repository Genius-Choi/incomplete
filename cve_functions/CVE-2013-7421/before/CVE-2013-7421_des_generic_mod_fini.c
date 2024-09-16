static void __exit des_generic_mod_fini(void)
{
	crypto_unregister_algs(des_algs, ARRAY_SIZE(des_algs));
}
