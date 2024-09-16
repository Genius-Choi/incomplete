static struct kwajd_stream *lzh_init(struct mspack_system *sys,
    struct mspack_file *in, struct mspack_file *out)
{
    struct kwajd_stream *lzh;

    if (!sys || !in || !out) return NULL;
    if (!(lzh = (struct kwajd_stream *) sys->alloc(sys, sizeof(struct kwajd_stream)))) return NULL;

    lzh->sys    = sys;
    lzh->input  = in;
    lzh->output = out;
    return lzh;
}
