static int vp7_calculate_mb_offset(int mb_x, int mb_y, int mb_width,
                                   int xoffset, int yoffset, int boundary,
                                   int *edge_x, int *edge_y)
{
    int vwidth = mb_width + 1;
    int new = (mb_y + yoffset) * vwidth + mb_x + xoffset;
    if (new < boundary || new % vwidth == vwidth - 1)
        return 0;
    *edge_y = new / vwidth;
    *edge_x = new % vwidth;
    return 1;
}
