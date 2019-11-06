enum class EnumClass : int{
e1,e2,e3
};
auto as_int =
    [](EnumClass a) -> typename std::underlying_type<EnumClass>::type {
  return static_cast<typename std::underlying_type<EnumClass>::type>(a);
};
