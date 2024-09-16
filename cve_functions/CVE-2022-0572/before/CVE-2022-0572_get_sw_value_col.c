get_sw_value_col(buf_T *buf, colnr_T col UNUSED)
{
    return buf->b_p_sw ? buf->b_p_sw :
#ifdef FEAT_VARTABS
	tabstop_at(col, buf->b_p_ts, buf->b_p_vts_array);
#else
	buf->b_p_ts;
#endif
}
