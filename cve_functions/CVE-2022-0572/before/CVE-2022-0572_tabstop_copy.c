tabstop_copy(int *oldts)
{
    int		*newts;
    int		t;

    if (oldts == NULL)
	return NULL;
    newts = ALLOC_MULT(int, oldts[0] + 1);
    if (newts != NULL)
	for (t = 0; t <= oldts[0]; ++t)
	    newts[t] = oldts[t];
    return newts;
}
