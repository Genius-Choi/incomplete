u32 a_copy_from_user(void *to, const void *from, u32 n)
{
    return(copy_from_user(to, from, n));
}
