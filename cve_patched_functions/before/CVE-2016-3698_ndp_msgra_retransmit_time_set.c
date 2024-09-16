void ndp_msgra_retransmit_time_set(struct ndp_msgra *msgra,
				   uint32_t retransmit_time)
{
	msgra->ra->nd_ra_retransmit = htonl(retransmit_time);
}
