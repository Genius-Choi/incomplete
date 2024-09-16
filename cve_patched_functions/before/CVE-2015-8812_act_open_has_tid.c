static inline int act_open_has_tid(int status)
{
	return status != CPL_ERR_TCAM_FULL && status != CPL_ERR_CONN_EXIST &&
	       status != CPL_ERR_ARP_MISS;
}
