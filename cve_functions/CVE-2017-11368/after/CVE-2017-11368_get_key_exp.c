get_key_exp(krb5_db_entry *entry)
{
    if (entry->expiration == 0)
        return entry->pw_expiration;
    if (entry->pw_expiration == 0)
        return entry->expiration;
    return ts_min(entry->expiration, entry->pw_expiration);
}
