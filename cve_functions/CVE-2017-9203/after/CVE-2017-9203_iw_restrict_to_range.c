static void iw_restrict_to_range(int r1, int r2, int *pvar)
{
	if(*pvar < r1) *pvar = r1;
	else if(*pvar > r2) *pvar = r2;
}
