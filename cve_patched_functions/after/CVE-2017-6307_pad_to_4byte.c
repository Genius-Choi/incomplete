pad_to_4byte (size_t length)
{
    return (length+3) & ~3;
}
