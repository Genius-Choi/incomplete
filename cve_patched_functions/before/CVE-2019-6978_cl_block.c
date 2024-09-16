cl_block (GifCtx *ctx)             /* table clear for block compress */
{

        cl_hash ( (count_int) hsize, ctx );
        ctx->free_ent = ctx->ClearCode + 2;
        ctx->clear_flg = 1;

        output( (code_int)ctx->ClearCode, ctx);
}
