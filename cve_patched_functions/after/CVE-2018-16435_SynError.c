cmsBool SynError(cmsIT8* it8, const char *Txt, ...)
{
    char Buffer[256], ErrMsg[1024];
    va_list args;

    va_start(args, Txt);
    vsnprintf(Buffer, 255, Txt, args);
    Buffer[255] = 0;
    va_end(args);

    snprintf(ErrMsg, 1023, "%s: Line %d, %s", it8->FileStack[it8 ->IncludeSP]->FileName, it8->lineno, Buffer);
    ErrMsg[1023] = 0;
    it8->sy = SSYNERROR;
    cmsSignalError(it8 ->ContextID, cmsERROR_CORRUPTION_DETECTED, "%s", ErrMsg);
    return FALSE;
}
