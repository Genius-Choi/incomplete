char *suhosin_cookie_decryptor(TSRMLS_D)
{
	char *raw_cookie = SG(request_info).cookie_data;
	char *decrypted, *ret, *var, *val, *tmp;
	int j;
	char cryptkey[33];

	/*
	if (...deactivated...) {
		return estrdup(raw_cookie);
	}
	*/

	suhosin_generate_key(SUHOSIN_G(cookie_cryptkey), SUHOSIN_G(cookie_cryptua), SUHOSIN_G(cookie_cryptdocroot), SUHOSIN_G(cookie_cryptraddr), (char *)&cryptkey TSRMLS_CC);

	ret = decrypted = emalloc(strlen(raw_cookie)*4+1);
	raw_cookie = estrdup(raw_cookie);
    SUHOSIN_G(raw_cookie) = estrdup(raw_cookie);

	
	j = 0; tmp = raw_cookie;
	while (*tmp) {
		char *d_url;int varlen;
		while (*tmp == '\t' || *tmp == ' ') tmp++;
		var = tmp;
		while (*tmp && *tmp != ';' && *tmp != '=') tmp++;
		
		varlen = tmp-var;
		/*memcpy(decrypted, var, varlen);
		decrypted += varlen;*/
		if (*tmp == 0) break;
		
		if (*tmp++ == ';') {
			*decrypted++ = ';';
			continue;
		}
		
		/**decrypted++ = '=';*/
		
		val = tmp;
		while (*tmp && *tmp != ';') tmp++;

		d_url = suhosin_decrypt_single_cookie(var, varlen, val, tmp-val, (char *)&cryptkey, &decrypted TSRMLS_CC);
		if (*tmp == ';') {
			*decrypted++ = ';';
		}
		
		if (*tmp == 0) break;
		tmp++;
	}
	*decrypted++ = 0;
	ret = erealloc(ret, decrypted-ret);
	
	SUHOSIN_G(decrypted_cookie) = ret;
	efree(raw_cookie);
		
	return ret;
}
