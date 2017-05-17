#!/usr/bin/python3

import subprocess
import os.path
import os

def main():
    print("*=========================================*")
    print("*          MAZE GENERATOR/SOLVER          *")
    print("*=========================================*")
    print()

    check_for_binaries()

    generate_call, unsolved = get_generation_call()
    solve_call = get_solve_call(unsolved)

    subprocess.call(generate_call.split())
    subprocess.call(solve_call.split())


def get_generation_call():
    print("How many rows (0 for maximum)?")
    rows = check_range(0, 100)

    print("How many cols (0 for maximum)?")
    cols = check_range(0, 200)

    print("Select a generation algorithm:")
    print("1) Randomized Prim's")
    print("2) Randomized Depth-First Search")
    print("2) Randomized Kruskal's")
    generation_alg = check_range(1, 3)

    print("Would you like to animate maze generation (y/n)?")
    animate_generation = yes_or_no()

    speed = 0
    if animate_generation:
        print("Enter animation speed (delay in milliseconds)")
        speed = check_range(0, 10000);

    print("Please enter a filename to save the unsolved maze to")
    filename = get_filename("unsolved.txt")

    generators = ['prims', 'dfs', 'kruskal']

    generate_call = "./generator_driver"
    generate_call += " --algorithm={}".format(generators[generation_alg-1])
    generate_call += " --file={}".format(filename)
    generate_call += " --animate" if animate_generation else ""
    generate_call += " --speed={}".format(speed if speed > 0 else "0")
    generate_call += " --rows={}".format(rows) if rows > 0 else ""
    generate_call += " --cols={}".format(cols) if cols > 0 else ""

    return generate_call, filename


def get_solve_call(input_file):
    print("Select a solving algorithm")
    print("1) Player Controlled")
    print("2) Recursive Backtracking")
    print("3) Breadth-First Search")
    print("4) Depth-First Search")
    print("5) A*")
    solve_alg = check_range(1, 5)

    speed = 0
    if solve_alg != 1:
        print("Would you like to animate maze solving (y/n)?")
        # animate_solve = True if input(">>>") == 'y' else False
        animate_solve = yes_or_no()
        if animate_solve:
            print("Enter animation speed (delay in milliseconds)")
            speed = check_range(0, 10000);
    else:
        animate_solve = True

    print("Please enter a filename to save the solved maze to")
    output_file = get_filename("solved.txt")

    solvers = ['play', 'bt', 'bfs', 'dfs', 'astar']

    solve_call = "./solver_driver"
    solve_call += " --algorithm={}".format(solvers[solve_alg-1])
    solve_call += " --animate" if animate_solve else ""
    solve_call += " --speed={}".format(speed if speed > 0 else "0")
    solve_call += " --infile={}".format(input_file)
    solve_call += " --outfile={}".format(output_file)

    return solve_call


def check_range(lower, upper):
    while True:
        val = input(">>>")
        if not val:
            return lower
        try:
            val = int(val)
            if (val < lower) or (val > upper):
                raise ValueError()
            return val
        except ValueError:
                error_msg = "ERROR: Please choose a number"
                error_msg += " between {} and {}".format(lower, upper)
                print(error_msg)


def yes_or_no():
    while True:
        val = input(">>>")
        if not val:
            return True
        if val.lower()[0] not in 'yn':
            error_msg = "ERROR: Please choose [y]es or [n]o "
            print(error_msg)
        else:
            return val[0] == 'y'


def check_for_binaries():
    generator_exists = os.path.isfile("./generator_driver")
    solver_exists = os.path.isfile("./solver_driver")
    if not (generator_exists and solver_exists):
        print("At least one of the necessary binaries does not exist")
        print("Attempt to resolve?")
        if yes_or_no():
            make_command = "make > /dev/null"
            FNULL = open(os.devnull, 'w')
            subprocess.call(make_command.split(), stdout=FNULL, stderr=FNULL)

            generator_exists = os.path.isfile("./generator_driver")
            solver_exists = os.path.isfile("./solver_driver")
            if not (generator_exists and solver_exists):
                print("Could not resolve. Try running make?")
                raise Exception("Please consult repo owner")
            else:
                print("\n=== Successfully built binaries ===\n")


def get_filename(default):
    val = input(">>>")
    if not val:
        return default
    else:
        return val

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\rGoodbye!")
    except Exception as e:
        print(e)
