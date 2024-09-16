static int jpg_decode_block(JPGContext *c, GetBitContext *gb,
                            int plane, int16_t *block)
{
    int dc, val, pos;
    const int is_chroma = !!plane;
    const uint8_t *qmat = is_chroma ? chroma_quant : luma_quant;

    c->dsp.clear_block(block);
    dc = get_vlc2(gb, c->dc_vlc[is_chroma].table, 9, 3);
    if (dc < 0)
        return AVERROR_INVALIDDATA;
    if (dc)
        dc = get_xbits(gb, dc);
    dc = dc * qmat[0] + c->prev_dc[plane];
    block[0] = dc;
    c->prev_dc[plane] = dc;

    pos = 0;
    while (pos < 63) {
        val = get_vlc2(gb, c->ac_vlc[is_chroma].table, 9, 3);
        if (val < 0)
            return AVERROR_INVALIDDATA;
        pos += val >> 4;
        val &= 0xF;
        if (pos > 63)
            return val ? AVERROR_INVALIDDATA : 0;
        if (val) {
            int nbits = val;

            val = get_xbits(gb, nbits);
            val *= qmat[ff_zigzag_direct[pos]];
            block[c->scantable.permutated[pos]] = val;
        }
    }
    return 0;
}
