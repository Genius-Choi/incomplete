lisp_match(char_u *p)
{
    char_u	buf[LSIZE];
    int		len;
    char_u	*word = *curbuf->b_p_lw != NUL ? curbuf->b_p_lw : p_lispwords;

    while (*word != NUL)
    {
	(void)copy_option_part(&word, buf, LSIZE, ",");
	len = (int)STRLEN(buf);
	if (STRNCMP(buf, p, len) == 0 && p[len] == ' ')
	    return TRUE;
    }
    return FALSE;
}
