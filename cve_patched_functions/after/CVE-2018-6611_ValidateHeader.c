static bool ValidateHeader(const STPFileHeader &fileHeader)
{
	if(std::memcmp(fileHeader.magic, "STP3", 4)
		|| fileHeader.version > 2
		|| fileHeader.numOrders > 128
		|| fileHeader.numSamples >= MAX_SAMPLES
		|| fileHeader.timerCount == 0
		|| fileHeader.midiCount != 50)
	{
		return false;
	}
	return true;
}
