static inline void __ap_schedule_poll_timer(void)
{
	ktime_t hr_time;

	spin_lock_bh(&ap_poll_timer_lock);
	if (hrtimer_is_queued(&ap_poll_timer) || ap_suspend_flag)
		goto out;
	if (ktime_to_ns(hrtimer_expires_remaining(&ap_poll_timer)) <= 0) {
		hr_time = ktime_set(0, poll_timeout);
		hrtimer_forward_now(&ap_poll_timer, hr_time);
		hrtimer_restart(&ap_poll_timer);
	}
out:
	spin_unlock_bh(&ap_poll_timer_lock);
}
