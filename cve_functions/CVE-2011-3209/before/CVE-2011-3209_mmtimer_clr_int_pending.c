static void mmtimer_clr_int_pending(int comparator)
{
	HUB_S((u64 *)LOCAL_MMR_ADDR(SH_EVENT_OCCURRED_ALIAS),
		SH_EVENT_OCCURRED_RTC1_INT_MASK << comparator);
}
