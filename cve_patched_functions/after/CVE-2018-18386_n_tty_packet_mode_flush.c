static void n_tty_packet_mode_flush(struct tty_struct *tty)
{
	unsigned long flags;

	if (tty->link->packet) {
		spin_lock_irqsave(&tty->ctrl_lock, flags);
		tty->ctrl_status |= TIOCPKT_FLUSHREAD;
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		wake_up_interruptible(&tty->link->read_wait);
	}
}
