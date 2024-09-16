init_key_type (struct key_type *kt, const char *ciphername,
	       bool ciphername_defined, const char *authname,
	       bool authname_defined, int keysize,
	       bool cfb_ofb_allowed, bool warn)
{
  CLEAR (*kt);
  if (ciphername && ciphername_defined)
    {
      kt->cipher = cipher_kt_get (translate_cipher_name_from_openvpn(ciphername));
      kt->cipher_length = cipher_kt_key_size (kt->cipher);
      if (keysize > 0 && keysize <= MAX_CIPHER_KEY_LENGTH)
	kt->cipher_length = keysize;

      /* check legal cipher mode */
      {
	const unsigned int mode = cipher_kt_mode (kt->cipher);
	if (!(mode == OPENVPN_MODE_CBC
#ifdef ALLOW_NON_CBC_CIPHERS
	      || (cfb_ofb_allowed && (mode == OPENVPN_MODE_CFB || mode == OPENVPN_MODE_OFB))
#endif
	      ))
#ifdef ENABLE_SMALL
	  msg (M_FATAL, "Cipher '%s' mode not supported", ciphername);
#else
	  msg (M_FATAL, "Cipher '%s' uses a mode not supported by " PACKAGE_NAME " in your current configuration.  CBC mode is always supported, while CFB and OFB modes are supported only when using SSL/TLS authentication and key exchange mode, and when " PACKAGE_NAME " has been built with ALLOW_NON_CBC_CIPHERS.", ciphername);
#endif
      }
    }
  else
    {
      if (warn)
	msg (M_WARN, "******* WARNING *******: null cipher specified, no encryption will be used");
    }
  if (authname && authname_defined)
    {
      kt->digest = md_kt_get (authname);
      kt->hmac_length = md_kt_size (kt->digest);
    }
  else
    {
      if (warn)
	msg (M_WARN, "******* WARNING *******: null MAC specified, no authentication will be used");
    }
}
