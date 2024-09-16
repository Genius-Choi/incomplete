int PKCS7_add_attribute(PKCS7_SIGNER_INFO *p7si, int nid, int atrtype,
                        void *value)
{
    return (add_attribute(&(p7si->unauth_attr), nid, atrtype, value));
}
