get_sw_value_pos(buf_T *buf, pos_T *pos)
{
    pos_T save_cursor = curwin->w_cursor;
    long sw_value;

    curwin->w_cursor = *pos;
    sw_value = get_sw_value_col(buf, get_nolist_virtcol());
    curwin->w_cursor = save_cursor;
    return sw_value;
}
