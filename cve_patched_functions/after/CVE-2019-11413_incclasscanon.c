static int incclasscanon(Reclass *cc, Rune c)
{
	Rune *p, r;
	for (p = cc->spans; p < cc->end; p += 2)
		for (r = p[0]; r <= p[1]; ++r)
			if (c == canon(r))
				return 1;
	return 0;
}
