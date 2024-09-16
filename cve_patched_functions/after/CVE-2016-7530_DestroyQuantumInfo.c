MagickExport QuantumInfo *DestroyQuantumInfo(QuantumInfo *quantum_info)
{
  assert(quantum_info != (QuantumInfo *) NULL);
  assert(quantum_info->signature == MagickCoreSignature);
  if (quantum_info->pixels != (unsigned char **) NULL)
    DestroyQuantumPixels(quantum_info);
  if (quantum_info->semaphore != (SemaphoreInfo *) NULL)
    RelinquishSemaphoreInfo(&quantum_info->semaphore);
  quantum_info->signature=(~MagickCoreSignature);
  quantum_info=(QuantumInfo *) RelinquishMagickMemory(quantum_info);
  return(quantum_info);
}
