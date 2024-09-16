static inline int sniffing_mode(struct airo_info *ai)
{
	return (le16_to_cpu(ai->config.rmode) & le16_to_cpu(RXMODE_MASK)) >=
		le16_to_cpu(RXMODE_RFMON);
}
