get_duplicate_name (const char *name,
                    int         count_increment,
                    int         max_length)
{
    char *result;
    char *name_base;
    const char *suffix;
    int count;

    parse_previous_duplicate_name (name, &name_base, &suffix, &count);
    result = make_next_duplicate_name (name_base, suffix, count + count_increment, max_length);

    g_free (name_base);

    return result;
}
