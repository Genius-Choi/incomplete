static int get_value(AVIOContext *pb, int type, int type2_size)
{
    switch (type) {
    case 2:
        return (type2_size == 32) ? avio_rl32(pb) : avio_rl16(pb);
    case 3:
        return avio_rl32(pb);
    case 4:
        return avio_rl64(pb);
    case 5:
        return avio_rl16(pb);
    default:
        return INT_MIN;
    }
}
