do_fixdel(exarg_T *eap UNUSED)
{
    char_u  *p;

    p = find_termcode((char_u *)"kb");
    add_termcode((char_u *)"kD", p != NULL
	    && *p == DEL ? (char_u *)CTRL_H_STR : DEL_STR, FALSE);
}
