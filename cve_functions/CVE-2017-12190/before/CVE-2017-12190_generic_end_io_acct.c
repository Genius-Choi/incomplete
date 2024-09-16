void generic_end_io_acct(struct request_queue *q, int rw,
			 struct hd_struct *part, unsigned long start_time)
{
	unsigned long duration = jiffies - start_time;
	int cpu = part_stat_lock();

	part_stat_add(cpu, part, ticks[rw], duration);
	part_round_stats(q, cpu, part);
	part_dec_in_flight(q, part, rw);

	part_stat_unlock();
}
