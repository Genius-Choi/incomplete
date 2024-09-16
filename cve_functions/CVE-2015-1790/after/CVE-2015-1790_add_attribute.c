static int add_attribute(STACK_OF(X509_ATTRIBUTE) **sk, int nid, int atrtype,
                         void *value)
{
    X509_ATTRIBUTE *attr = NULL;

    if (*sk == NULL) {
        if ((*sk = sk_X509_ATTRIBUTE_new_null()) == NULL)
            return 0;
 new_attrib:
        if ((attr = X509_ATTRIBUTE_create(nid, atrtype, value)) == NULL)
            return 0;
        if (!sk_X509_ATTRIBUTE_push(*sk, attr)) {
            X509_ATTRIBUTE_free(attr);
            return 0;
        }
    } else {
        int i;

        for (i = 0; i < sk_X509_ATTRIBUTE_num(*sk); i++) {
            attr = sk_X509_ATTRIBUTE_value(*sk, i);
            if (OBJ_obj2nid(X509_ATTRIBUTE_get0_object(attr)) == nid) {
                X509_ATTRIBUTE_free(attr);
                attr = X509_ATTRIBUTE_create(nid, atrtype, value);
                if (attr == NULL)
                    return 0;
                if (!sk_X509_ATTRIBUTE_set(*sk, i, attr)) {
                    X509_ATTRIBUTE_free(attr);
                    return 0;
                }
                goto end;
            }
        }
        goto new_attrib;
    }
 end:
    return (1);
}
