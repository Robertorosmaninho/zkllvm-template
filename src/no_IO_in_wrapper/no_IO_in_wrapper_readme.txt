Results in
```
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
```

Probably due to parsing the filename as string.
We expected to read it on the main function and then call the circuit with the
right arguments, which we now realise is not the case.
