u32 ReadVirtIODeviceRegister(ULONG_PTR ulRegister)
{
    ULONG ulValue;

    NdisRawReadPortUlong(ulRegister, &ulValue);

    DPrintf(6, ("[%s]R[%x]=%x\n", __FUNCTION__, (ULONG)ulRegister, ulValue) );
    return ulValue;
}
