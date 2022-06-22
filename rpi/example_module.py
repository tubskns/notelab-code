def calc_sum(values):
    sum_result = 0
    for value in values:
        sum_result += value
    return sum_result


def calc_avg(values):
    avg = calc_sum(values) / len(values)
    return avg


if __name__ == "__main__":
    my_avg = calc_avg([1, 1, 1, 10])
    print("The average is: " + str(my_avg))
