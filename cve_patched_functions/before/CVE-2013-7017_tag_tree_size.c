static int32_t tag_tree_size(uint16_t w, uint16_t h)
{
    uint32_t res = 0;
    while (w > 1 || h > 1) {
        res += w * h;
        av_assert0(res + 1 < INT32_MAX);
        w = (w + 1) >> 1;
        h = (h + 1) >> 1;
    }
    return (int32_t)(res + 1);
}
