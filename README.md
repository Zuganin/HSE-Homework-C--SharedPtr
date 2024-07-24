In this README file, I want to talk about the task that needed to be completed, my solution is in the Shared_ptr.h files. 

Task

Implement the SharedPtr template, a simplified analogue of the smart pointer class with shared ownership.
The idea of the implementation: in addition to the pointer to the allocated resource itself, it is necessary to know the number of "strong" and "weak" references to the object.
To do this, we will allocate a special strong_counter counter in the heap, which will store this information (when creating a new pointer, the corresponding counter increases, when deleting it decreases; if the number of strong references has become 0, then the object is deleted).

Implementation Details

The details were discussed at lectures and seminars. The SharedPtr template class must support:
The default constructor (creates a null pointer).
Constructor from the pointer (saves the pointer to the owned object).
Copy constructor and copying assignment (create a new reference to the same object).
The moving constructor and the moving assignment must transfer ownership of the object.
The Reset method(T* ptr = nullptr), changes the pointer that the object owns.
The Swap method(SharedPtr&).
The Get() method that returns a pointer to the owned object.
The UseCount() method, which returns the number of "strong" references to the object.
Dereference operator operator*.
The "arrow" operator is operator->.
An explicit conversion operator to bool (operator bool).
