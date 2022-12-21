## Sorting algorithm comparison

 1'000'000| Random        | Sorted        | Reverse sorted|
----------| ------------- |---------------|---------------|
 Heapsort | 175.31ms      | 88.42ms       | 93.66ms       |
 Quicksort| 99.80ms       | 768195.74ms   | 639533.27ms   |
 Mergesort| 343.26ms      | 186.52ms      | 205.90ms      |
 
### Summary:

1. Heapsort - this algorithm doesn't perform that well with random arrangement, but it is decent with sorted and reverse sorted arrays, probably because it already resembles a heap and makes it easier to heapify.
2. Quicksort - probably the best algorithm out there, but unfortunately the pivot selection method chosen shows its biggest weakness -  it's not uncommon to find the worst case scenario (O(n^2) time and space complexity). That's why the pivot selection is a very important step and should be carefully implemented.
3. Mergesort - it seems like the worst algorithm out of all 3, but you have to keep in mind that I didn't implement any major optimizations, such as: adding a threshold to deal with smaller arrays (like insertion sort for n <= 10), possibly reducing copy operations, etc.

### Conclusion

In the end, I think that all of these algorithms are very useful. The C++ implementation of std::sort is usually an introsort - a combination of quicksort, heapsort and insertion sort, while the std::stable_sort is always a mergesort.