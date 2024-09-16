tabstop_padding(colnr_T col, int ts_arg, int *vts)
{
    int		ts = ts_arg == 0 ? 8 : ts_arg;
    int		tabcount;
    colnr_T	tabcol = 0;
    int		t;
    int		padding = 0;

    if (vts == NULL || vts[0] == 0)
	return ts - (col % ts);

    tabcount = vts[0];

    for (t = 1; t <= tabcount; ++t)
    {
	tabcol += vts[t];
	if (tabcol > col)
	{
	    padding = (int)(tabcol - col);
	    break;
	}
    }
    if (t > tabcount)
	padding = vts[tabcount] - (int)((col - tabcol) % vts[tabcount]);

    return padding;
}
