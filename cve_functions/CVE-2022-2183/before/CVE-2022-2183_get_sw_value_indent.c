get_sw_value_indent(buf_T *buf)
{
    pos_T pos = curwin->w_cursor;

    pos.col = getwhitecols_curline();
    return get_sw_value_pos(buf, &pos);
}
