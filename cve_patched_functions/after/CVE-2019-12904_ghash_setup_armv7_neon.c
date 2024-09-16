ghash_setup_armv7_neon (gcry_cipher_hd_t c)
{
  _gcry_ghash_setup_armv7_neon(c->u_mode.gcm.u_ghash_key.key);
}
