static void khugepaged_alloc_sleep(void)
{
	DEFINE_WAIT(wait);
	add_wait_queue(&khugepaged_wait, &wait);
	schedule_timeout_interruptible(
		msecs_to_jiffies(
			khugepaged_alloc_sleep_millisecs));
	remove_wait_queue(&khugepaged_wait, &wait);
}
