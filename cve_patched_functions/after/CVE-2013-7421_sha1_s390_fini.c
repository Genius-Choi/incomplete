static void __exit sha1_s390_fini(void)
{
	crypto_unregister_shash(&alg);
}
