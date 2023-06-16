The test compiles and generates a proof. However, the assignment table with `add`
as the circuit is
10  5   15  0   0   0   0   0
showing that the inputs were 10 and 5, and output was 15, instead of the
intended 30.


Also, when using `mul` as the circuit we have the current assignment table:
5	10	0	0	0	0	0	0
which is even more confusing.

The input of the program is the circuit function regardless if it is main
or not, and the wrapper is ignored.
