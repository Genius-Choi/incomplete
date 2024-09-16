static int mov_realloc_extradata(AVCodecParameters *par, MOVAtom atom)
{
    int err = 0;
    uint64_t size = (uint64_t)par->extradata_size + atom.size + 8 + AV_INPUT_BUFFER_PADDING_SIZE;
    if (size > INT_MAX || (uint64_t)atom.size > INT_MAX)
        return AVERROR_INVALIDDATA;
    if ((err = av_reallocp(&par->extradata, size)) < 0) {
        par->extradata_size = 0;
        return err;
    }
    par->extradata_size = size - AV_INPUT_BUFFER_PADDING_SIZE;
    return 0;
}
