static void tg3_hwclock_to_timestamp(struct tg3 *tp, u64 hwclock,
				     struct skb_shared_hwtstamps *timestamp)
{
	memset(timestamp, 0, sizeof(struct skb_shared_hwtstamps));
	timestamp->hwtstamp  = ns_to_ktime((hwclock & TG3_TSTAMP_MASK) +
					   tp->ptp_adjust);
}
