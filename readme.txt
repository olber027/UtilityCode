Code that should hopefully come in handy at some point.
-----------------
Sort.h
-----------------
Provides static functions for most basic sorting algorithms. Each takes an array
and the size of the array as parameters. Also provides an isSorted function.
All sorting is done in place, and will modify the given array.

-----------------
BinaryTree.h
-----------------
Provides a templated Node class consisting of a pointer to a left and right child, if they exist.
As well as the value of that node. The Binary Tree class contains a pointer to a root node, as
well as numerous tree accessor and manipulation functions.

-----------------
Dictionary.h
-----------------
Provides a templated dictionary class. Lookup times are done in log(n) when searching by key.
New entries must be made using the addEntry function. Attempts to access a key that does not
exist will result in an exception.

-----------------
Graph.h
-----------------
- VertexType
    The virtual base class for use in the vertex class. Any types used in the Vertex class must
    inherit from this class. All vertex types must be able to provide an integer cost from
    itself to a given vertex. They must also provide a string representation.
- Vertex
    This is the class for vertices of the graph. The template type must derive from VertexType.
    It contains a list of neighbors it can reach as well as methods to connect and disconnect
    new vertices.
- Path
    This contains an in order list of pointers from the given starting vertex to the given
    destination vertex. A path is what is returned from any of the graph searching functions.
- Graph
    This contains a list of vertices along with information about the graph including numVertices
    and numEdges. Also contains graph manipulation functionality and searching functionality.

-----------------
LinkedList.h
-----------------
Provides a templated linkedlist class along with a corresponding node class.
Contains all the standard linkedlist functionality.

-----------------
Set.h
-----------------
Provides a templated set class. This collection can only take one of any given element. All standard
set operations have been implemented.

-----------------
Stack.h
-----------------
Standard templated Stack class.

-----------------
ArgEnsure.h
-----------------
A class to ensure that arguments passed into a program align with expected inputs. relies on Regex.h

-----------------
Regex.h
-----------------
Standard regex class. Each instance can have a matching pattern which it will attempt to match given
text against. Uses the Thompson regular expression algorithm.

-----------------
SmartPointer.h
-----------------
Reference counted pointer implementation.

-----------------
SmartString.h
-----------------
Provides a whole bunch of string manipulation functionality. Can do most anything you'd want to do with
strings.