//https://stackoverflow.com/questions/43195778/push-back-variadic-function-parameters-into-a-vector

namespace cpp17 {
void foo(Rest... rest) {
    (x.push_back(rest), ...);
}
}

namespace cpp14{

void foo(Rest... rest) {
    int a[] = {0, (x.push_back(rest), 0)...};
    static_cast<void>(a);  // unused
}
}
