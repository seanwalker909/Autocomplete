Binary Search Tree implementation of the 'Autocomplete as you type' feature found on popular search engines. 

Program demonstrates the following Binary Search Tree (BST) concepts / operations:
-inserting into a BST
-recursive and higher level traversals of BSTs to find nodes
-calculating depth and height of BSTs

There are 3 source files. Compile and run using:
gcc main.c bst.c -o Autocomplete -Wall
./Autocomplete

1. when the program starts, enter the name of the file you want to use:
cities.txt
cities2.txt
cities-by-population.txt
fortune-1000.txt
fortune-1000-by-revenue.txt

the program will use the text file to generate a Binary Search Tree.

******
EXAMPLE
******
if the user enteres:
suggest 5 Chi
this means they want to be show the top 5 weighted queries that start with the prefix Chi:

**Sample Run**

** Starting Autocomplete **
Please enter a file name: 
 cities.txt 
 cities-by-population.txt 
 fortune1000.txt 
 fortune1000-by-revenue.txt 
cities.txt
** Ready **
add 4000000 ChinaTown
**Added
suggest 5 Chi
** [Sub-tree root:  (Chittagong, Bangladesh,3920222)]
** [Sub-tree count: 69]
** [Num matches:    49]
ChinaTown - 4000000
Chittagong, Bangladesh - 3920222
Chicago, Illinois, United States - 2695598
Chiba-shi, Japan - 919729
Chihuahua, Chihuahua, Mexico - 708267

