static int put_cacheinfo(struct sk_buff *skb, unsigned long cstamp,
			 unsigned long tstamp, u32 preferred, u32 valid)
{
	struct ifa_cacheinfo ci;

	ci.cstamp = cstamp_delta(cstamp);
	ci.tstamp = cstamp_delta(tstamp);
	ci.ifa_prefered = preferred;
	ci.ifa_valid = valid;

	return nla_put(skb, IFA_CACHEINFO, sizeof(ci), &ci);
}
