static void __exit exit_dns_resolver(void)
{
	key_revoke(dns_resolver_cache->thread_keyring);
	unregister_key_type(&key_type_dns_resolver);
	put_cred(dns_resolver_cache);
}
