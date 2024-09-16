S_with_queued_errors(pTHX_ SV *ex)
{
    PERL_ARGS_ASSERT_WITH_QUEUED_ERRORS;
    if (PL_errors && SvCUR(PL_errors) && !SvROK(ex)) {
	sv_catsv(PL_errors, ex);
	ex = sv_mortalcopy(PL_errors);
	SvCUR_set(PL_errors, 0);
    }
    return ex;
}
