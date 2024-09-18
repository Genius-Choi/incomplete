static void __exit sha1_generic_mod_fini(void)
{
	crypto_unregister_shash(&alg);
}
