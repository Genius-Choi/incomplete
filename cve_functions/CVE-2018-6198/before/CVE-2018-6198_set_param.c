set_param(char *name, char *value)
{
    struct param_ptr *p;
    double ppc;

    if (value == NULL)
	return 0;
    p = search_param(name);
    if (p == NULL)
	return 0;
    switch (p->type) {
    case P_INT:
	if (atoi(value) >= 0)
	    *(int *)p->varptr = (p->inputtype == PI_ONOFF)
		? str_to_bool(value, *(int *)p->varptr) : atoi(value);
	break;
    case P_NZINT:
	if (atoi(value) > 0)
	    *(int *)p->varptr = atoi(value);
	break;
    case P_SHORT:
	*(short *)p->varptr = (p->inputtype == PI_ONOFF)
	    ? str_to_bool(value, *(short *)p->varptr) : atoi(value);
	break;
    case P_CHARINT:
	*(char *)p->varptr = (p->inputtype == PI_ONOFF)
	    ? str_to_bool(value, *(char *)p->varptr) : atoi(value);
	break;
    case P_CHAR:
	*(char *)p->varptr = value[0];
	break;
    case P_STRING:
	*(char **)p->varptr = value;
	break;
#if defined(USE_SSL) && defined(USE_SSL_VERIFY)
    case P_SSLPATH:
	if (value != NULL && value[0] != '\0')
	    *(char **)p->varptr = rcFile(value);
	else
	    *(char **)p->varptr = NULL;
	ssl_path_modified = 1;
	break;
#endif
#ifdef USE_COLOR
    case P_COLOR:
	*(int *)p->varptr = str_to_color(value);
	break;
#endif
#ifdef USE_M17N
    case P_CODE:
	*(wc_ces *) p->varptr =
	    wc_guess_charset_short(value, *(wc_ces *) p->varptr);
	break;
#endif
    case P_PIXELS:
	ppc = atof(value);
	if (ppc >= MINIMUM_PIXEL_PER_CHAR && ppc <= MAXIMUM_PIXEL_PER_CHAR * 2)
	    *(double *)p->varptr = ppc;
	break;
    case P_SCALE:
	ppc = atof(value);
	if (ppc >= 10 && ppc <= 1000)
	    *(double *)p->varptr = ppc;
	break;
    }
    return 1;
}
