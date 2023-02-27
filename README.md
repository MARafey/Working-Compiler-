# Working Compiler along with image processing
This code is using C++ and the OpenCV library to implement some data structures and functions related to image processing. Here's a brief description of what each part does:

* node class: a template class that represents a node in a linked list. It contains two data members (data and data2) and a pointer to the next node.
* node_0 class: a template class that represents a node in a stack. It contains one data member (data) and a pointer to the next node.
* queue class: a template class that represents a queue data structure. It uses the node class to implement the linked list.
* Stack class: a template class that represents a stack data structure. It uses the node_0 class to implement the linked list.
* LRU class: a template class that represents a Least Recently Used (LRU) cache. It uses the node class to implement the linked list.
* compare function: a template function that compares a given string with the strings stored in an LRU cache. If the string is found in the cache, it moves the corresponding node to the front of the list and returns true. Otherwise, it returns false.
* image_pixel_pickeing function: a template function that takes an image and converts it to a 2D array of floats representing the grayscale values of each pixel.
* display_new_image function: a template function that takes a 2D array of grayscale values and displays it as an image.

Overall, this code provides some basic building blocks for image processing using C++ and OpenCV.

The program begins by including several libraries necessary for working with images, such as OpenCV and iostream. OpenCV (Open Source Computer Vision Library) is a powerful library of programming functions used for real-time computer vision. It provides many algorithms for image processing, such as image filtering, object detection, and image segmentation, and supports many platforms, including Windows, Linux, and Android. The iostream library, on the other hand, provides input/output capabilities for working with text files.

The program then defines several classes and data structures that will be used in the rest of the program. The first class is a template class called "node" that represents a node in a linked list. A linked list is a data structure consisting of a sequence of nodes, each containing a reference to the next node in the sequence. The "node" class has two data members, "data" and "data2", both of type T, and a pointer to the next node in the sequence, "next". The "node" class also has a constructor that takes two arguments, "d" and "d2", and initializes the "data" and "data2" members with them.

The second class is another template class called "node_0" that represents a node in a stack. A stack is a data structure that allows elements to be added and removed only from one end, called the top. The "node_0" class has one data member, "data", of type T, and a pointer to the next node in the stack, "next". The "node_0" class also has a constructor that takes one argument, "d", and initializes the "data" member with it.

The third class is a template class called "queue" that represents a queue data structure, which is a first-in, first-out (FIFO) data structure. The "queue" class has two pointer data members, "front" and "back", which respectively point to the front and back of the queue. The "queue" class has three member functions: "push", "pop", and "IsEmpty". The "push" function takes two arguments, "x" and "y", creates a new node with these values, and adds it to the back of the queue. The "pop" function removes the front node from the queue. The "IsEmpty" function returns true if the queue is empty, and false otherwise.

The fourth class is the "Stack" class, which is similar to the "node_0" class but implements the stack data structure instead. It has one pointer data member, "top", which points to the top of the stack. The "Stack" class has three member functions: "push", "pop", and "IsEmpty". The "push" function adds a new node with the given value to the top of the stack. The "pop" function removes the top node from the stack. The "IsEmpty" function returns true if the stack is empty, and false otherwise.

The LRU class is a templated class that implements the Least Recently Used (LRU) algorithm to manage a cache of items.
* The class has a constructor that initializes the front and back pointers to NULL and the size of the cache to 0.
* The push method takes two arguments, x and y, and adds a new node with those values to the back of the cache. If the cache is empty, it sets both the front and back pointers to the new node.
* The pop method removes the front node of the cache, if it exists, and updates the front pointer and the size of the cache.
* The getdata_1 method returns the data value of the front node of the cache.
* The getdata_2 method returns the second data value of the front node of the cache.
* The getsize method returns the current size of the cache.
* The IsEmpty method checks if the cache is empty and returns a boolean value.
* The compare function takes a LRU object lru and a string a as arguments. It creates a temporary LRU object temp3.
* The function loops through the cache using the getdata_1 and getdata_2 methods to retrieve the data values of the nodes.
* If the first data value of a node matches the string a, the function moves all the nodes in temp3 back to the original cache and returns true.
* If the first data value of a node does not match the string a, the function pushes the node's data values to temp3 and pops the node from the original cache.
* After the loop, if the string a was not found in the cache, the function moves all the nodes in temp3 back to the original cache and returns false.
