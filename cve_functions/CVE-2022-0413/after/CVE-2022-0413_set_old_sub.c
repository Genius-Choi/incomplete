set_old_sub(char_u *val)
{
    vim_free(old_sub);
    old_sub = val;
}
