tabstop_at(colnr_T col, int ts, int *vts)
{
    int		tabcount;
    colnr_T	tabcol = 0;
    int		t;
    int		tab_size = 0;

    if (vts == 0 || vts[0] == 0)
	return ts;

    tabcount = vts[0];
    for (t = 1; t <= tabcount; ++t)
    {
	tabcol += vts[t];
	if (tabcol > col)
	{
	    tab_size = vts[t];
	    break;
	}
    }
    if (t > tabcount)
	tab_size = vts[tabcount];

    return tab_size;
}
