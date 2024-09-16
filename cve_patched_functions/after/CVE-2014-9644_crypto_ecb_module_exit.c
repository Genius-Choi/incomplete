static void __exit crypto_ecb_module_exit(void)
{
	crypto_unregister_template(&crypto_ecb_tmpl);
}
