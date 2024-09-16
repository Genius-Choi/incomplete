static void t1_flush_cs(boolean is_subr)
{
    char *p;
    byte *r, *return_cs = NULL;
    cs_entry *tab, *end_tab, *ptr;
    char *start_line, *line_end;
    int count, size_pos;
    unsigned short cr, cs_len = 0;      /* to avoid warning about uninitialized use of cs_len */
    if (is_subr) {
        start_line = subr_array_start;
        line_end = subr_array_end;
        size_pos = subr_size_pos;
        tab = subr_tab;
        count = subr_max + 1;
        end_tab = subr_tab + count;
    } else {
        start_line = cs_dict_start;
        line_end = cs_dict_end;
        size_pos = cs_size_pos;
        tab = cs_tab;
        end_tab = cs_ptr;
        count = cs_count;
    }
    t1_line_ptr = t1_line_array;
    for (p = start_line; p - start_line < size_pos;)
        *t1_line_ptr++ = *p++;
    while (isdigit((unsigned char)*p))
        p++;
    sprintf(t1_line_ptr, "%u", count);
    strcat(t1_line_ptr, p);
    t1_line_ptr = eol(t1_line_array);
    t1_putline();

    /* create return_cs to replace unused subr's */
    if (is_subr) {
        cr = 4330;
        cs_len = 0;
        /* at this point we have t1_lenIV >= 0;
         * a negative value would be caught in t1_scan_param() */
        return_cs = xtalloc(t1_lenIV + 1, byte);
        for (cs_len = 0, r = return_cs; cs_len < t1_lenIV; cs_len++, r++)
            *r = cencrypt(0x00, &cr);
        *r = cencrypt(CS_RETURN, &cr);
        cs_len++;
    }

    for (ptr = tab; ptr < end_tab; ptr++) {
        if (ptr->used) {
            if (is_subr)
                sprintf(t1_line_array, "dup %lu %u",
                        (unsigned long) (ptr - tab), ptr->cslen);
            else
                sprintf(t1_line_array, "/%s %u", ptr->name, ptr->cslen);
            p = strend(t1_line_array);
            memcpy(p, ptr->data, ptr->len);
            t1_line_ptr = p + ptr->len;
            t1_putline();
        } else {
            /* replace unsused subr's by return_cs */
            if (is_subr) {
                sprintf(t1_line_array, "dup %lu %u%s ",
                        (unsigned long) (ptr - tab), cs_len, cs_token_pair[0]);
                p = strend(t1_line_array);
                memcpy(p, return_cs, cs_len);
                t1_line_ptr = p + cs_len;
                t1_putline();
                sprintf(t1_line_array, " %s", cs_token_pair[1]);
                t1_line_ptr = eol(t1_line_array);
                t1_putline();
            }
        }
        xfree(ptr->data);
        if (ptr->name != notdef)
            xfree(ptr->name);
    }
    sprintf(t1_line_array, "%s", line_end);
    t1_line_ptr = eol(t1_line_array);
    t1_putline();
    if (is_subr)
        xfree(return_cs);
    xfree(tab);
    xfree(start_line);
    xfree(line_end);
}
