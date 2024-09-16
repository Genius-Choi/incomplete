static void n_tty_write_wakeup(struct tty_struct *tty)
{
	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	kill_fasync(&tty->fasync, SIGIO, POLL_OUT);
}
