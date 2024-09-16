void blk_mq_enable_hotplug(void)
{
	mutex_unlock(&all_q_mutex);
}
