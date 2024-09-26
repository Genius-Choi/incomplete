struct nls_table *load_nls_default(void)
{
	struct nls_table *default_nls;
	
	default_nls = load_nls(CONFIG_NLS_DEFAULT);
	if (default_nls != NULL)
		return default_nls;
	else
		return &default_table;
}
