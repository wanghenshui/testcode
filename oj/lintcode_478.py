class Calculator:
    """
    @param a: An integer
    @param operator: A character, +, -, *, /.
    @param b: An integer
    @return: The result
    """
    def calculate(self, a, operator, b):
        # write your code here
        switcher = {
            "+": lambda a,b:a+b,
            "-": lambda a,b:a-b,
            "*": lambda a,b:a*b,
            "/": lambda a,b:a/b
        }
        return switcher.get(operator)(a,b)

