### Project description
> This is a learning project to investigate some programming features like algorythms and 
> data structures and to try ThreadX-RTOS. By writing of this project was used the "Introduction to Algorithms
> Third Edition" by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein.

> Languages: C/C++;
> Build system: Make

> Project was builded and tested on Ubuntu/Linux.

### Build for Ubuntu/Linux
Go to the project's root:
```sh
cd <path_to_project_root>
```
If release folder exists in project's root, delete it before:
```sh
rm -r release
```
In project's root make a release directory:
```sh
mkdir release
```
Run make to build the project:
```sh
make compile_flags="-O2 -g -DCHECK_SORT_ALGORITHMS=1 -DCHECK_DATA_STRUCTURES=1" --directory=release --makefile=../makefile
```
To execute program enter the command:
```sh
./release/linux_release
```

### Preprocessor flags description
|  Flag  | Description |
| ------ | ----------- |
| -DCHECK_SORT_ALGORITHMS | Enable algorythms to compile and check |
| -DCHECK_DATA_STRUCTURES | Enable data structures to compile and check |

### Sources description

1. ThreadX-RTOS was used mostly as a memory and time manager to count of resources usage by algorithms.
2. In "algorithms" folder some sort algorythms are imlemented  like insertion sort, selection sort, merge sort and quick sort on C for a char-array.
3. In "data_structures" folder stack and queue are implemented on C for char data type.
4. In "data_structures" folder doubly linked list and binary tree are implemented on C++ for uint32_t data type.
