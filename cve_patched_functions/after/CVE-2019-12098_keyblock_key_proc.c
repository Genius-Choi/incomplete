keyblock_key_proc(krb5_context context, krb5_enctype enctype,
		  krb5_const_pointer keyseed,
		  krb5_salt salt, krb5_data *s2kparms,
		  krb5_keyblock **key)
{
    return krb5_copy_keyblock (context, keyseed, key);
}
