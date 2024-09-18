static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV410P,            AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_GRAY8,              AV_PIX_FMT_YUV444P,
        AV_PIX_FMT_YUV422P,            AV_PIX_FMT_YUV411P,
        AV_PIX_FMT_YUV440P,
        AV_PIX_FMT_NONE
    };

    ff_set_common_formats(ctx, ff_make_format_list(pix_fmts));

    return 0;
}
