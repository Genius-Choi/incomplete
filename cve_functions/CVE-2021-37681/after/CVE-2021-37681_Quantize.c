inline TfLiteStatus Quantize(TfLiteContext* context, float scale,
                             int32_t zero_point, float f, int32_t& q) {
  const float tmp = TfLiteRound(f / scale);
  const bool no_integer_overflow_from_quantization =
      (tmp >= static_cast<float>(std::numeric_limits<int32_t>::min()) &&
       tmp <= static_cast<float>(std::numeric_limits<int32_t>::max()));
  TF_LITE_ENSURE(context, no_integer_overflow_from_quantization);
  q = zero_point + static_cast<int32_t>(tmp);
  return kTfLiteOk;
}
