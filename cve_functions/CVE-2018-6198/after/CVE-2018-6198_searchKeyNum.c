searchKeyNum(void)
{
    char *d;
    int n = 1;

    d = searchKeyData();
    if (d != NULL)
	n = atoi(d);
    return n * PREC_NUM;
}
