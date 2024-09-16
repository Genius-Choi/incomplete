otp_return_padata(krb5_context context, krb5_pa_data *padata,
                  krb5_data *req_pkt, krb5_kdc_req *request,
                  krb5_kdc_rep *reply, krb5_keyblock *encrypting_key,
                  krb5_pa_data **send_pa_out, krb5_kdcpreauth_callbacks cb,
                  krb5_kdcpreauth_rock rock, krb5_kdcpreauth_moddata moddata,
                  krb5_kdcpreauth_modreq modreq)
{
    krb5_keyblock *armor_key = NULL;

    if (padata->length == 0)
        return 0;

    /* Get the armor key. */
    armor_key = cb->fast_armor(context, rock);
    if (!armor_key) {
      com_err("otp", ENOENT, "No armor key found when returning padata");
      return ENOENT;
    }

    /* Replace the reply key with the FAST armor key. */
    krb5_free_keyblock_contents(context, encrypting_key);
    return krb5_copy_keyblock_contents(context, armor_key, encrypting_key);
}
