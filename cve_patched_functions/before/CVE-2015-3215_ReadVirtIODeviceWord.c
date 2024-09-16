u16 ReadVirtIODeviceWord(ULONG_PTR ulRegister)
{
    u16 wValue;

    NdisRawReadPortUshort(ulRegister, &wValue);

    DPrintf(6, ("[%s]R[%x]=%x\n", __FUNCTION__, (ULONG)ulRegister, wValue) );

    return wValue;
}
