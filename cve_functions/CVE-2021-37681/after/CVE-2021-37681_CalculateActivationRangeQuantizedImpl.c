TfLiteStatus CalculateActivationRangeQuantizedImpl(
    TfLiteContext* context, TfLiteFusedActivation activation, int32_t qmin,
    int32_t qmax, TfLiteTensor* output, int32_t* act_min, int32_t* act_max) {
  const auto scale = output->params.scale;
  const auto zero_point = output->params.zero_point;

  int32_t tmp_q;
  if (activation == kTfLiteActRelu) {
    TF_LITE_ENSURE_OK(context,
                      Quantize(context, scale, zero_point, 0.0, tmp_q));
    *act_min = std::max(qmin, tmp_q);
    *act_max = qmax;
  } else if (activation == kTfLiteActRelu6) {
    TF_LITE_ENSURE_OK(context,
                      Quantize(context, scale, zero_point, 0.0, tmp_q));
    *act_min = std::max(qmin, tmp_q);
    TF_LITE_ENSURE_OK(context,
                      Quantize(context, scale, zero_point, 6.0, tmp_q));
    *act_max = std::min(qmax, tmp_q);
  } else if (activation == kTfLiteActReluN1To1) {
    TF_LITE_ENSURE_OK(context,
                      Quantize(context, scale, zero_point, -1.0, tmp_q));
    *act_min = std::max(qmin, tmp_q);
    TF_LITE_ENSURE_OK(context,
                      Quantize(context, scale, zero_point, 1.0, tmp_q));
    *act_max = std::min(qmax, tmp_q);
  } else {
    *act_min = qmin;
    *act_max = qmax;
  }
  return kTfLiteOk;
}
