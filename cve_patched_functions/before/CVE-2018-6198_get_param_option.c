get_param_option(char *name)
{
    struct param_ptr *p;

    p = search_param(name);
    return p ? to_str(p)->ptr : NULL;
}
