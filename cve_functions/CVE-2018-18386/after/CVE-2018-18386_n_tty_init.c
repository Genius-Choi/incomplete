void __init n_tty_init(void)
{
	tty_register_ldisc(N_TTY, &n_tty_ops);
}
