int TfLiteTypeGetSize(TfLiteType type) {
  switch (type) {
    case kTfLiteUInt8:
      static_assert(sizeof(uint8_t) == 1, "");
      return 1;
    case kTfLiteInt8:
      static_assert(sizeof(int8_t) == 1, "");
      return 1;
    case kTfLiteBool:
      return sizeof(bool);
    case kTfLiteInt16:
      static_assert(sizeof(int16_t) == 2, "");
      return 2;
    case kTfLiteFloat16:
      static_assert(sizeof(int16_t) == 2, "");
      return 2;
    case kTfLiteFloat32:
      static_assert(sizeof(float) == 4, "");
      return 4;
    case kTfLiteInt32:
      static_assert(sizeof(int32_t) == 4, "");
      return 4;
    case kTfLiteUInt32:
      static_assert(sizeof(uint32_t) == 4, "");
      return 4;
    case kTfLiteInt64:
      static_assert(sizeof(int64_t) == 8, "");
      return 8;
    case kTfLiteUInt64:
      static_assert(sizeof(uint64_t) == 8, "");
      return 8;
    case kTfLiteFloat64:
      static_assert(sizeof(double) == 8, "");
      return 8;
    case kTfLiteComplex64:
      static_assert(sizeof(std::complex<float>) == 8, "");
      return 8;
    case kTfLiteComplex128:
      static_assert(sizeof(std::complex<double>) == 16, "");
      return 16;
    default:
      return 0;
  }
}
