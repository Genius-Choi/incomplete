Perl_savesvpv(pTHX_ SV *sv)
{
    STRLEN len;
    const char * const pv = SvPV_const(sv, len);
    char *newaddr;

    PERL_ARGS_ASSERT_SAVESVPV;

    ++len;
    Newx(newaddr,len,char);
    return (char *) CopyD(pv,newaddr,len,char);
}
