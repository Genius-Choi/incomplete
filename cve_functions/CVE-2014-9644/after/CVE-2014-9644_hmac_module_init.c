static int __init hmac_module_init(void)
{
	return crypto_register_template(&hmac_tmpl);
}
