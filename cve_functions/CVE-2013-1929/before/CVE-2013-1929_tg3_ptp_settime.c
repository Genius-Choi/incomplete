static int tg3_ptp_settime(struct ptp_clock_info *ptp,
			   const struct timespec *ts)
{
	u64 ns;
	struct tg3 *tp = container_of(ptp, struct tg3, ptp_info);

	ns = timespec_to_ns(ts);

	tg3_full_lock(tp, 0);
	tg3_refclk_write(tp, ns);
	tp->ptp_adjust = 0;
	tg3_full_unlock(tp);

	return 0;
}
