static int init_thread_copy(AVCodecContext *avctx)
{
    FFV1Context *f = avctx->priv_data;

    f->picture.f      = NULL;
    f->last_picture.f = NULL;
    f->sample_buffer  = NULL;
    f->quant_table_count = 0;
    f->slice_count = 0;

    return 0;
}
