static void __exit twofish_mod_fini(void)
{
	crypto_unregister_alg(&alg);
}
