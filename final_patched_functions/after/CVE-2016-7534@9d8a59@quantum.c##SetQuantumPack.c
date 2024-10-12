MagickExport void SetQuantumPack(QuantumInfo *quantum_info,
  const MagickBooleanType pack)
{
  assert(quantum_info != (QuantumInfo *) NULL);
  assert(quantum_info->signature == MagickCoreSignature);
  quantum_info->pack=pack;
}
