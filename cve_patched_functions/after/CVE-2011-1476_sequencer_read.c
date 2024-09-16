int sequencer_read(int dev, struct file *file, char __user *buf, int count)
{
	int c = count, p = 0;
	int ev_len;
	unsigned long flags;

	dev = dev >> 4;

	ev_len = seq_mode == SEQ_1 ? 4 : 8;

	spin_lock_irqsave(&lock,flags);

	if (!iqlen)
	{
		spin_unlock_irqrestore(&lock,flags);
 		if (file->f_flags & O_NONBLOCK) {
  			return -EAGAIN;
  		}

 		interruptible_sleep_on_timeout(&midi_sleeper,
					       pre_event_timeout);
		spin_lock_irqsave(&lock,flags);
		if (!iqlen)
		{
			spin_unlock_irqrestore(&lock,flags);
			return 0;
		}
	}
	while (iqlen && c >= ev_len)
	{
		char *fixit = (char *) &iqueue[iqhead * IEV_SZ];
		spin_unlock_irqrestore(&lock,flags);
		if (copy_to_user(&(buf)[p], fixit, ev_len))
			return count - c;
		p += ev_len;
		c -= ev_len;

		spin_lock_irqsave(&lock,flags);
		iqhead = (iqhead + 1) % SEQ_MAX_QUEUE;
		iqlen--;
	}
	spin_unlock_irqrestore(&lock,flags);
	return count - c;
}
