tabstop_eq(int *ts1, int *ts2)
{
    int		t;

    if ((ts1 == 0 && ts2) || (ts1 && ts2 == 0))
	return FALSE;
    if (ts1 == ts2)
	return TRUE;
    if (ts1[0] != ts2[0])
	return FALSE;

    for (t = 1; t <= ts1[0]; ++t)
	if (ts1[t] != ts2[t])
	    return FALSE;

    return TRUE;
}
