u8 ReadVirtIODeviceByte(ULONG_PTR ulRegister)
{
    u8 bValue;

    NdisRawReadPortUchar(ulRegister, &bValue);

    DPrintf(6, ("[%s]R[%x]=%x\n", __FUNCTION__, (ULONG)ulRegister, bValue) );

    return bValue;
}
