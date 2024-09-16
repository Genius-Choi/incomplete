check_decryption_preparation (RIJNDAEL_context *ctx)
{
  if ( !ctx->decryption_prepared )
    {
      prepare_decryption ( ctx );
      ctx->decryption_prepared = 1;
    }
}
