# AlvVector
Vector class made by me, features a lot of the same features as the stranded vector class. Small Header only library.

# .At(size_t index)
Returns element in vector at specfied index

# .capacity()
Returns the current capacity of the vector

# .Clear()
Clears the vector but also allocates 2 extra spaces for further use of the vector

# .Emplace(size_t index, const Args&... args)
Will insert a number of varibles from the starting index specifed onwards

# .EmplaceBack(const Args&... args)
Same as .Emplace() but will enter new elements at the end

# .Find(const T& searchElem)
Tries to find the element provided in the vector. Returns the index of the item; if they item is not found it returns -1

# .Insert(const T& data, size_t index) | .Insert(T&& data, size_t index)
Inserts the passed element at the specifed index

# .isEmpty()
Returns true if the vector has 0 elements, false if otherwise

# .PopBack()
Removes the last element

# .PushBack(const T& data) | PushBack(T&& data)
Pushes the new element to the end of the vector

# .Remove(size_t index)
Removes the element at the specifed index. If the removal is successfull the method returns true, otherwise, false.

# .Reserve(size_t newSize)
Reserves the amount of space indicated. If the wanted space is smaller then current capacity, nothing will happen

# .Resize(size_t newSize, const T& fillData)
Will resize the vector to the new size. If the new size is greater then current capacity space will be allocated. If the new space is larger then the current space it will fill the extra space with the filler data provided. If the space is smaller it will remove any elements beyond the specifed space

# .Shrink()
Method will shrink capacity to be withen the confines of the current size
