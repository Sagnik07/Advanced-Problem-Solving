# Advanced-Problem-Solving

Problem 1

Problem Statement: Implement ordered set with suitable data structure.

An ordered set is a common data structure that supports O(log N) lookups, insertions
and removals. Ordered set is also sometimes used as an alternative to a hash map, for
example in STL’s map.

Following operation should be implemented on ordered set.

O(log N) insertion and removal.

O(log N) check if contains a value.

O(log N) to find the element in the set closest to some value.

O(log N) to find k-th largest element in the set.

O(log N) to count the number of elements in the set whose values fall into a
given range.


Problem 2

In a sorted array of integers , median of the array is defined as follows

● If there are odd numbers of elements in an array , median element is the middle
of that array E.x [ 1 , 2 , 3] median is 2 and for [ 1 , 3 , 3] median is 3

● If there are even numbers of elements in an array , median element is average of
two middle elements of that array E.x [ 1 , 2 , 3 , 4 ] median is ( 2 + 3 ) / 2 and for
[ 1 , 3 , 3 , 5 ] median is 3.

Problem Description​ : Given a stream of integers , after occurrence of every
number , output the median of array.

Example:​ Given sequence is 5 , 7 , 1 , 6 , 2 , 3

Explanation:​ [ 5 ] median is 5 [ 5 , 7] median is (5+7)/2 [ 5 7 1 ] sorted array is
[1 5 7 ] median is 5 [5 7 1 6] sorted array is [1 5 6 7] median is (5 + 6)/2.


Problem 3

Problem Statement : Nth no. of a unsorted array

Task: To find the nth smallest element in a given sequence. The operation should take
an amortized cost of O(n).

Aim: To learn how to use randomization in algorithms.

Hint: Think of the partition function of randomized quick-sort.

Testing: Time your function using time.h and compare it with the Standard Library Function
nth_element().


Problem 4

Problem Statement: Find Articulation point in a graph

For a disconnected undirected graph, an articulation point is a vertex removing which
increases number of connected components.

NOTE: You are not allowed to use STLs or any other inbuilt libraries.


Problem 5

Problem Statement: Implementation of suffix array

Implement a Suffix Array that is capable of performing following operations on Strings in a
most efficient way.

Given a string S print its minimum lexicographic rotation. ​ O(nlogn)

String consist of either Lower/Upper Case Alphabet and Numeric digits.

Example :

S = “dcabca”

1. All possible rotation are “dcabca” , “cabcad” , “abcadc” , “bcadca” , “cadcab” , “adcabc” .
Among all lexicographically minimum is “abcadc” .


Problem 6

Problem Statement: Trie Implementation

Given an array ​ A ​ of ​ N ​ numbers, you will be given ​ q ​ queries.

Each query will contain a single integer ​ x.​ You have to find then maximum xor of ​ x ​ from any
number in ​ A.

Constraints :

1 <= N, q <= 1 0 5

1 <= A[i] <= 1 0 12

Example :

A = {1, 2, 3}

x = 4

Maximum xor of x is with 3, therefore answer is 4 xor 3 = 7


Problem 7

External Sorting

Problem Statement: External Sorting is a class of algorithms used to deal with massive
amounts of data that do not fit in memory. The questions aim at implementing one such type:
K-Way merge sort algorithm to sort a very large array. This algorithm is a perfect example of
the use of divide and conquer where with limited resources large problems are tackled by
breaking the problem space into small computable subspaces and then operations are done
on them.

Input Constraints:

1. A file containing a large unsorted list of integers (Will not fit in your usual
Laptop RAM).

2.Do not use any in-built data structures.

Output : A file containing non-Descending sorted list of the given integers

Languages allowed : C, C++, Python Evaluation parameters :

1. Time and Space Complexity of the algorithm

2. Efficient use of Data-Structures

Example Format:

If your input file is at ./data/input.txt And if you need your output file at ./data/ named
output.txt
