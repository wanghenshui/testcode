class Greeter:
  def __init__(self, name):
    self.name = name
    print(f"hello, {self.name}!")
    
  def __enter__(self):
    return self

  def __exit__(self, e_type, e_val, e_tb):
    print(f"goodbye, {self.name}!")

    
def main():
  with Greeter(1):
    print("we have a greeter")

main()
