errcode_to_protocol(krb5_error_code code)
{
    int protcode;

    protcode = code - ERROR_TABLE_BASE_krb5;
    return (protcode >= 0 && protcode <= 128) ? protcode : KRB_ERR_GENERIC;
}
