class Foo {
  ~Foo() = default;
  int x = 0;
};

class Bar {
  ~Bar() {}
  int x = 0;
};

void foo_cpy(Foo f1, Foo& f2) {
  f2 = f1;
}

void bar_cpy(Bar b1, Bar& b2) {
  b2 = b1;
}
