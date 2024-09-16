rijndael_encrypt (void *context, byte *b, const byte *a)
{
  RIJNDAEL_context *ctx = context;

  if (ctx->prefetch_enc_fn)
    ctx->prefetch_enc_fn();

  return ctx->encrypt_fn (ctx, b, a);
}
