// Skycrapers Puzzle - Piscine42-2024/9
//   - Coding method: 
//      - A) Check incoming parameters
//           Return error codes:
//              Err1) No arguments or too many
//              Err2) Argument string too long or too short
//              Err3) Error in view numbers
//              Err4) No solution found
//      - B) Create a 2D tab index for expected view numbers 
//           (extracted from parameters)
//             row key -> value left 
//           & row key -> value right
//                Views tab order:
//                   0)col1up     1)col2up    2)col3up      3)col4up 
//                   4)col1down   5)col2down  6)col3down    7)col4down 
//                   8)row1left   9)row2left  10)row3left  11)row4left
//                  12)row1right 13)row2right 14)row3right 15)row4right
//      - C) Browse the map recursively placing one new value & incrementing it
//      - D) Check every time every row & every column
//             (checking factorized by transposing the map matrix)
//   - Compilation:
//        > cc -Wall -Wextra -Werror -o rush-01 *.c
//   - Execution:
//        > ./rush-01 "col1up col2up col3up col4up col1down col2down col3down 
//        col4down row1left row2left row3left row4left row1right row2right ro
//        w3right row4right"
//   - Example:
//        > ./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
//     Output:
//        1 2 3 4
//        2 3 4 1
//        3 4 1 2
//        4 1 2 3

