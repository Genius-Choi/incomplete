ar6000_regDomain_event(struct ar6_softc *ar, u32 regCode)
{
    A_PRINTF("AR6000 Reg Code = 0x%x\n", regCode);
    ar->arRegCode = regCode;
}
