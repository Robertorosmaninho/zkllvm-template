#2 tries to update a global within the circuit. We test the base case of globals being mutable.
#3 uses globals to set the value of a local struct, and uses it locally. (editado) 
#4 is like #3, but passes it to another function to use it, that only reads it.
#5 is like #4 but the struct is also updated, not only initialized.

Results:
#2: Segmentation fault
#3: Segmentation fault
#4:
bitcast
terminate called after throwing an instance of 'std::bad_cast'
   what():  std::bad_cast
#5:
bitcast
terminate called after throwing an instance of 'std::bad_cast'
  what():  std::bad_cast
