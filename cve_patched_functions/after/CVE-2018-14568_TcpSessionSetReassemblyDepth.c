void TcpSessionSetReassemblyDepth(TcpSession *ssn, uint32_t size)
{
    if (size > ssn->reassembly_depth || size == 0) {
        ssn->reassembly_depth = size;
    }

    return;
}
