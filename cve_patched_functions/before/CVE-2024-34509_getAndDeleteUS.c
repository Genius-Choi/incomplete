getAndDeleteUS(DcmDataset *obj, DcmTagKey t, Uint16 *us)
{
    OFCondition cond = getUS(obj, t, us); PRET(cond, t);
    cond = deleteElem(obj, t);
    return cond;
}
