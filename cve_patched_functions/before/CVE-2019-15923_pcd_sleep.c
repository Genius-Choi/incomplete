static void pcd_sleep(int cs)
{
	schedule_timeout_interruptible(cs);
}
