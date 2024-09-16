static unsigned int find_best_mtu(const struct t3c_data *d, unsigned short mtu)
{
	int i = 0;

	while (i < d->nmtus - 1 && d->mtus[i + 1] <= mtu)
		++i;
	return i;
}
