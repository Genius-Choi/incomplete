n_tty_receive_char_flagged(struct tty_struct *tty, unsigned char c, char flag)
{
	switch (flag) {
	case TTY_BREAK:
		n_tty_receive_break(tty);
		break;
	case TTY_PARITY:
	case TTY_FRAME:
		n_tty_receive_parity_error(tty, c);
		break;
	case TTY_OVERRUN:
		n_tty_receive_overrun(tty);
		break;
	default:
		tty_err(tty, "unknown flag %d\n", flag);
		break;
	}
}
