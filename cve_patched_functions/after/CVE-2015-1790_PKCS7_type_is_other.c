static int PKCS7_type_is_other(PKCS7 *p7)
{
    int isOther = 1;

    int nid = OBJ_obj2nid(p7->type);

    switch (nid) {
    case NID_pkcs7_data:
    case NID_pkcs7_signed:
    case NID_pkcs7_enveloped:
    case NID_pkcs7_signedAndEnveloped:
    case NID_pkcs7_digest:
    case NID_pkcs7_encrypted:
        isOther = 0;
        break;
    default:
        isOther = 1;
    }

    return isOther;

}
