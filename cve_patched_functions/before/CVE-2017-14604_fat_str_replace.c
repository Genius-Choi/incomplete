fat_str_replace (char *str,
                 char  replacement)
{
    gboolean success;
    int i;

    success = FALSE;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (strchr (FAT_FORBIDDEN_CHARACTERS, str[i]) ||
            str[i] < 32)
        {
            success = TRUE;
            str[i] = replacement;
        }
    }

    return success;
}
