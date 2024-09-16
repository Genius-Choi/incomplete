static void __exit srpt_cleanup_module(void)
{
	ib_unregister_client(&srpt_client);
	target_unregister_template(&srpt_template);
}
