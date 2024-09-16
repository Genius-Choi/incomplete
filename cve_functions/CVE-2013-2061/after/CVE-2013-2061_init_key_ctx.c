init_key_ctx (struct key_ctx *ctx, struct key *key,
	      const struct key_type *kt, int enc,
	      const char *prefix)
{
  struct gc_arena gc = gc_new ();
  CLEAR (*ctx);
  if (kt->cipher && kt->cipher_length > 0)
    {

      ALLOC_OBJ(ctx->cipher, cipher_ctx_t);
      cipher_ctx_init (ctx->cipher, key->cipher, kt->cipher_length,
	  kt->cipher, enc);

      msg (D_HANDSHAKE, "%s: Cipher '%s' initialized with %d bit key",
          prefix,
          cipher_kt_name(kt->cipher),
          kt->cipher_length *8);

      dmsg (D_SHOW_KEYS, "%s: CIPHER KEY: %s", prefix,
          format_hex (key->cipher, kt->cipher_length, 0, &gc));
      dmsg (D_CRYPTO_DEBUG, "%s: CIPHER block_size=%d iv_size=%d",
          prefix,
          cipher_kt_block_size(kt->cipher),
          cipher_kt_iv_size(kt->cipher));
    }
  if (kt->digest && kt->hmac_length > 0)
    {
      ALLOC_OBJ(ctx->hmac, hmac_ctx_t);
      hmac_ctx_init (ctx->hmac, key->hmac, kt->hmac_length, kt->digest);

      msg (D_HANDSHAKE,
      "%s: Using %d bit message hash '%s' for HMAC authentication",
      prefix, md_kt_size(kt->digest) * 8, md_kt_name(kt->digest));

      dmsg (D_SHOW_KEYS, "%s: HMAC KEY: %s", prefix,
	  format_hex (key->hmac, kt->hmac_length, 0, &gc));

      dmsg (D_CRYPTO_DEBUG, "%s: HMAC size=%d block_size=%d",
	prefix,
	md_kt_size(kt->digest),
	hmac_ctx_size(ctx->hmac));

    }
  gc_free (&gc);
}
