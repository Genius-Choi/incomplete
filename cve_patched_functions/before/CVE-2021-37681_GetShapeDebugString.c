std::string GetShapeDebugString(const TfLiteIntArray* shape) {
  std::string str;
  for (int d = 0; d < shape->size; ++d) {
    if (str.empty())
      str = "[" + std::to_string(shape->data[d]);
    else
      str += ", " + std::to_string(shape->data[d]);
  }
  str += "]";
  return str;
}
