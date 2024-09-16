_gcry_cipher_gcm_setkey (gcry_cipher_hd_t c)
{
  memset (c->u_mode.gcm.u_ghash_key.key, 0, GCRY_GCM_BLOCK_LEN);

  c->spec->encrypt (&c->context.c, c->u_mode.gcm.u_ghash_key.key,
                    c->u_mode.gcm.u_ghash_key.key);
  setupM (c);
}
