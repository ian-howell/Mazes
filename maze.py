#!/usr/bin/python3

import subprocess

def main():
    print("*=========================================*")
    print("*          MAZE GENERATOR/SOLVER          *")
    print("*=========================================*")
    print()

    generate_call, unsolved = get_generation_call()
    solve_call = get_solve_call(unsolved)

    subprocess.call(generate_call.split())
    subprocess.call(solve_call.split())


def get_generation_call():
    print("How many rows (0 for maximum)?")
    rows = int(input(">>>"))
    print("How many cols (0 for maximum)?")
    cols = int(input(">>>"))
    print("Select a generation algorithm:")
    print("1) Randomized Prim's")
    generation_alg = check_range(1, 1)
    print("Would you like to animate maze generation (y/n)?")
    animate_generation = True if input(">>>") == 'y' else False
    print("Please enter a filename to save the unsolved maze to")
    filename = input(">>>")

    generators = ['prims']

    generate_call = "./generator_driver"
    generate_call += " --algorithm={}".format(generators[generation_alg-1])
    generate_call += " --file={}".format(filename)
    generate_call += " --animate" if animate_generation else ""
    generate_call += " --rows={}".format(rows) if rows > 0 else ""
    generate_call += " --cols={}".format(cols) if cols > 0 else ""

    return generate_call, filename


def get_solve_call(input_file):
    print("Select a solving algorithm")
    print("1) Player Controlled")
    print("2) Recursive Backtracking")
    print("3) Breadth-First Search")
    print("4) Depth-First Search")
    solve_alg = check_range(1, 4)
    if solve_alg != 1:
        print("Would you like to animate maze solving (y/n)?")
        animate_solve = True if input(">>>") == 'y' else False
    else:
        animate_solve = False
    print("Please enter a filename to save the solved maze to")
    output_file = input(">>>")

    solvers = ['play', 'bt', 'bfs', 'dfs']

    solve_call = "./solver_driver"
    solve_call += " --algorithm={}".format(solvers[solve_alg-1])
    solve_call += " --animate" if animate_solve else ""
    solve_call += " --infile={}".format(input_file)
    solve_call += " --outfile={}".format(output_file)

    return solve_call


def check_range(lower, upper):
    val = int(input(">>>"))

    error_msg = "ERROR: Please choose a number"
    error_msg += " between {} and {}".format(lower, upper)
    while (val < lower) or (val > upper):
        print(error_msg)
        val = int(input(">>>"))
    return val


if __name__ == "__main__":
    main()
