int wc_ecc_point_is_at_infinity(ecc_point* p)
{
    if (p == NULL)
        return BAD_FUNC_ARG;

    if (get_digit_count(p->x) == 0 && get_digit_count(p->y) == 0)
        return 1;

    return 0;
}
