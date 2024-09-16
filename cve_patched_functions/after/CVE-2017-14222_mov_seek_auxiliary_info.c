static int mov_seek_auxiliary_info(MOVContext *c, MOVStreamContext *sc, int64_t index)
{
    size_t auxiliary_info_seek_offset = 0;
    int i;

    if (sc->cenc.auxiliary_info_default_size) {
        auxiliary_info_seek_offset = (size_t)sc->cenc.auxiliary_info_default_size * index;
    } else if (sc->cenc.auxiliary_info_sizes) {
        if (index > sc->cenc.auxiliary_info_sizes_count) {
            av_log(c, AV_LOG_ERROR, "current sample %"PRId64" greater than the number of auxiliary info sample sizes %"SIZE_SPECIFIER"\n",
                index, sc->cenc.auxiliary_info_sizes_count);
            return AVERROR_INVALIDDATA;
        }

        for (i = 0; i < index; i++) {
            auxiliary_info_seek_offset += sc->cenc.auxiliary_info_sizes[i];
        }
    }

    if (auxiliary_info_seek_offset > sc->cenc.auxiliary_info_end - sc->cenc.auxiliary_info) {
        av_log(c, AV_LOG_ERROR, "auxiliary info offset %"SIZE_SPECIFIER" greater than auxiliary info size %"SIZE_SPECIFIER"\n",
            auxiliary_info_seek_offset, (size_t)(sc->cenc.auxiliary_info_end - sc->cenc.auxiliary_info));
        return AVERROR_INVALIDDATA;
    }

    sc->cenc.auxiliary_info_pos = sc->cenc.auxiliary_info + auxiliary_info_seek_offset;
    sc->cenc.auxiliary_info_index = index;
    return 0;
}
