check_regexp_delim(int c)
{
    if (isalpha(c))
    {
	emsg(_(e_regular_expressions_cant_be_delimited_by_letters));
	return FAIL;
    }
    return OK;
}
