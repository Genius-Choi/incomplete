static int mov_read_saiz(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    MOVStreamContext *sc;
    size_t data_size;
    int atom_header_size;
    int flags;

    if (c->decryption_key_len == 0 || c->fc->nb_streams < 1)
        return 0;

    st = c->fc->streams[c->fc->nb_streams - 1];
    sc = st->priv_data;

    if (sc->cenc.auxiliary_info_sizes || sc->cenc.auxiliary_info_default_size) {
        av_log(c->fc, AV_LOG_ERROR, "duplicate saiz atom\n");
        return AVERROR_INVALIDDATA;
    }

    atom_header_size = 9;

    avio_r8(pb); /* version */
    flags = avio_rb24(pb);

    if ((flags & 0x01) != 0) {
        atom_header_size += 8;

        avio_rb32(pb);    /* info type */
        avio_rb32(pb);    /* info type param */
    }

    sc->cenc.auxiliary_info_default_size = avio_r8(pb);
    avio_rb32(pb);    /* entries */

    if (atom.size <= atom_header_size) {
        return 0;
    }

    if (atom.size > FFMIN(INT_MAX, SIZE_MAX)) {
        av_log(c->fc, AV_LOG_ERROR, "saiz atom auxiliary_info_sizes size %"PRId64" invalid\n", atom.size);
        return AVERROR_INVALIDDATA;
    }

    /* save the auxiliary info sizes as is */
    data_size = atom.size - atom_header_size;

    sc->cenc.auxiliary_info_sizes = av_malloc(data_size);
    if (!sc->cenc.auxiliary_info_sizes) {
        return AVERROR(ENOMEM);
    }

    sc->cenc.auxiliary_info_sizes_count = data_size;

    if (avio_read(pb, sc->cenc.auxiliary_info_sizes, data_size) != data_size) {
        av_log(c->fc, AV_LOG_ERROR, "failed to read the auxiliary info sizes");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}
