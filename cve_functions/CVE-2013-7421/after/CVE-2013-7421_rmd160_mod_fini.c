static void __exit rmd160_mod_fini(void)
{
	crypto_unregister_shash(&alg);
}
