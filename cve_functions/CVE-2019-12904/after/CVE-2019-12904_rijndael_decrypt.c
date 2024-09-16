rijndael_decrypt (void *context, byte *b, const byte *a)
{
  RIJNDAEL_context *ctx = context;

  check_decryption_preparation (ctx);

  if (ctx->prefetch_dec_fn)
    ctx->prefetch_dec_fn();

  return ctx->decrypt_fn (ctx, b, a);
}
