#ifndef SRC_UTILS_MACROS_H_
#define SRC_UTILS_MACROS_H_

#define SWAP(x, y, T) do { T SWAP = (x); (x) = (y); (y) = SWAP; } while (0)

#define MIN(a,b) (((a)<(b))?(a):(b))

#endif /* SRC_UTILS_MACROS_H_ */
