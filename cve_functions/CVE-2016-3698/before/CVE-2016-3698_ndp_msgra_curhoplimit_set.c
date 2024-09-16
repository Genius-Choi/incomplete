void ndp_msgra_curhoplimit_set(struct ndp_msgra *msgra, uint8_t curhoplimit)
{
	msgra->ra->nd_ra_curhoplimit = curhoplimit;
}
