ASC_abortAssociation(T_ASC_Association * association)
{
    if (association == NULL) return ASC_NULLKEY;
    if (association->DULassociation == NULL) return ASC_NULLKEY;

    OFCondition cond = DUL_AbortAssociation(&association->DULassociation);
    return cond;
}
