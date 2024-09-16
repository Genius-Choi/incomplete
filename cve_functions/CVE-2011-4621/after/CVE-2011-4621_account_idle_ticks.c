void account_idle_ticks(unsigned long ticks)
{
	account_idle_time(jiffies_to_cputime(ticks));
}
