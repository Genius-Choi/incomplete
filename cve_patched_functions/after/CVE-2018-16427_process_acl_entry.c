static u8 process_acl_entry(sc_file_t *in, unsigned int method, unsigned int in_def)
{
	u8 def = (u8)in_def;
	const sc_acl_entry_t *entry = sc_file_get_acl_entry(in, method);
	if (!entry)
	{
		return def;
	}
	else if (entry->method & SC_AC_CHV)
	{
		unsigned int key_ref = entry->key_ref;
		if (key_ref == SC_AC_KEY_REF_NONE)
			return def;
		else
			return ENTERSAFE_AC_ALWAYS&0x04;
	}
	else if (entry->method & SC_AC_NEVER)
	{
		return ENTERSAFE_AC_NEVER;
	}
	else
	{
		return def;
	}
}
