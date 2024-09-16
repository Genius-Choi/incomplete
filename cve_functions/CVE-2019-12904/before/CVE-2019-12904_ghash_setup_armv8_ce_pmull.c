ghash_setup_armv8_ce_pmull (gcry_cipher_hd_t c)
{
  _gcry_ghash_setup_armv8_ce_pmull(c->u_mode.gcm.u_ghash_key.key,
                                   c->u_mode.gcm.gcm_table);
}
