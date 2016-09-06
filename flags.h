#ifndef FLAGS_H
#define FLAGS_H

#define ANIMATE check_bit(flags, 0)
#define MAN_SOLVE !check_bit(flags, 2) && check_bit(flags, 1)
#define BACKTRACK_SOLVE check_bit(flags, 2) && !check_bit(flags, 1)
#define PRINT_UNSOLVED !check_bit(flags, 4) && check_bit(flags, 3)
#define PRINT_SOLVED check_bit(flags, 4) && !check_bit(flags, 3)
#define PRINT_BOTH check_bit(flags, 4) && check_bit(flags, 3)

#endif
