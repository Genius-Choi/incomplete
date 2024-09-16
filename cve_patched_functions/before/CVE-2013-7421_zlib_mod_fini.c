static void __exit zlib_mod_fini(void)
{
	crypto_unregister_pcomp(&zlib_alg);
}
