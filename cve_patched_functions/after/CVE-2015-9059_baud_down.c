baud_down (int baud)
{
	int nb;
	nb = term_baud_down(baud);
	if (nb == 0)
		nb = baud;
	return nb;
}
