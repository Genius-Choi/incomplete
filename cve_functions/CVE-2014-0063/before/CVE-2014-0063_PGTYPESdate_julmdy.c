PGTYPESdate_julmdy(date jd, int *mdy)
{
	int			y,
				m,
				d;

	j2date((int) (jd + date2j(2000, 1, 1)), &y, &m, &d);
	mdy[0] = m;
	mdy[1] = d;
	mdy[2] = y;
}
