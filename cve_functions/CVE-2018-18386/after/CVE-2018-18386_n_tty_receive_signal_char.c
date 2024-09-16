n_tty_receive_signal_char(struct tty_struct *tty, int signal, unsigned char c)
{
	isig(signal, tty);
	if (I_IXON(tty))
		start_tty(tty);
	if (L_ECHO(tty)) {
		echo_char(c, tty);
		commit_echoes(tty);
	} else
		process_echoes(tty);
	return;
}
