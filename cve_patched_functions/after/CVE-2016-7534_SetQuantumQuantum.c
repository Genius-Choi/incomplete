MagickExport void SetQuantumQuantum(QuantumInfo *quantum_info,
  const size_t quantum)
{
  assert(quantum_info != (QuantumInfo *) NULL);
  assert(quantum_info->signature == MagickCoreSignature);
  quantum_info->quantum=quantum;
}
