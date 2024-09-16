static char *revealextraspc(char * const s_)
{
    unsigned char *s = (unsigned char *) s_;
    unsigned char *sn;
    
    if (s == NULL) {
        return s_;
    }
    simplify(s_);
    while (*s != 0U && isspace(*s)) {
        *s++ = '_';
    }
    if (*s == 0U) {
        return s_;
    }
    sn = s;
    do {
        sn++;
    } while (*sn != 0U);
    do {
        sn--;        
        if (!isspace(*sn)) {
            break;
        }
        *sn = '_';
    } while (sn != s);
    
    return s_;
}
