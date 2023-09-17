# Task
Implement quicksort and time the function. Implement an improved quicksort where you assume that the elements before and after
the section that the quicksort function is currently at is bounded by the values before and after that section, since these values
were previous pivot points. If these two values are equal, that means that all numbers in the current section are equal too, and so
checks for that whole section can be skipped. Measure the overhead required for this and test the running time on arrays with a lot
of duplicates and with no duplicates.

### Notes
For some reason this task does not work unless the -Ofast flag is passed when compiled. Not sure why, but I don't have time to fix
this for now...
