#ifndef FLAGS_H
#define FLAGS_H

#define ANIMATE_GEN check_bit(flags, 0)

#define ANIMATE_SOLVE check_bit(flags, 2) || check_bit(flags, 1)
#define MAN_SOLVE !check_bit(flags, 2) && check_bit(flags, 1)
#define BACKTRACK_SOLVE check_bit(flags, 2) && !check_bit(flags, 1)
#define BFS_SOLVE check_bit(flags, 2) && check_bit(flags, 1)

#define PRINT_UNSOLVED check_bit(flags, 4)
#define PRINT_SOLVED check_bit(flags, 3)

#endif
