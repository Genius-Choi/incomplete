u8 llc_data_accept_state(u8 state)
{
	return state != LLC_CONN_STATE_NORMAL && state != LLC_CONN_STATE_BUSY &&
	       state != LLC_CONN_STATE_REJ;
}
