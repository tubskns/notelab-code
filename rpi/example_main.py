import example_module as em

def check_sign(value):
    if value > 0:
        print("Calculated value", value, "is positive")
    elif value == 0:
        print("Calculated value", value, "is equal to zero")
    else:
        print("Calculated value", value, "is negative")

###### first task
check_sign(-5)

###### second task
value = em.calc_sum([2, -5, 8, -13])
check_sign(value)




    