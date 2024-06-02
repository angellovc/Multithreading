## Executing the code

1. Compile the code

```
gcc -g map-reduce-algo.c thread.c string_map.c read_file.c -o word_counter

```

2. Execute the code

```
./word_counter <Text File>
```

I.E:
```
./word_counter lorem.txt
```

## Memory leak analyzer 

```
leaks -atExit -- ./word_counter lorem.txt

```