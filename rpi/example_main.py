import example_module as em


def check_sign(value):
    if value > 0:
        print("Value: ", value, "is positive")
    elif value == 0:
        print("Value:", value, "is equal to zero")
    else:
        print("Value:", value, "is negative")


check_sign(-5)

value = em.calc_sum([2, -5, 8, -13])
check_sign(value)
