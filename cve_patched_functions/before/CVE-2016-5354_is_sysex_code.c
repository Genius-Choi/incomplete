is_sysex_code(guint8 code)
{
    return (code == 0x04 || code == 0x05 || code == 0x06 || code == 0x07);
}
