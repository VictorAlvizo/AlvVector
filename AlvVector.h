#pragma once
#include <iostream>

template<typename T>
class AlvVector {
public:
	template<typename ... Args>
	AlvVector(const Args&... args) {
		AllocateMem(2);
		AddRecur(args...);
	}

	AlvVector() {
		AllocateMem(2);
	}

	~AlvVector() {
		m_Size = 0;
		m_Capacity = 0;
		delete[] m_Data;
		m_Data = nullptr;
	}

	void Clear() {
		m_Size = 0;
		m_Capacity = 0;
		delete[] m_Data;
		m_Data = nullptr;

		AllocateMem(2);
	}

	void Resize(size_t newSize, const T& fillData) {
		if (newSize >= m_Capacity) {
			AllocateMem(newSize + 1);
		}

		if (m_Size > newSize) { //If new size is smaller then current size, remove elements until at n pos
			for (unsigned int i = newSize; i < m_Size; i++) { //Remove all data that extends beyond n pos
				m_Data[i].~T();
			}

			m_Size = newSize;
		}
		else if (newSize > m_Size) { //If new size is bigger than current size, fill it with the data provided
			std::cout << "Here" << std::endl;

			for (unsigned int i = m_Size; i < newSize; i++) {
				m_Data[i] = fillData;
			}

			m_Size = newSize;
		}
	}

	void Reserve(size_t newSize) {
		if (m_Capacity < newSize) {
			AllocateMem(newSize);
		}
	}

	void Shrink() {
		AllocateMem(m_Size);
	}

	void PushBack(const T& data) {
		if (m_Size + 1 == m_Capacity) {
			AllocateMem(m_Capacity + 5); //Everytime capacity is hit reserve 5 spaces
		}

		m_Data[m_Size++] = data;
	}

	void PushBack(T&& data) { //Move rvalue varibles instead of having to copy them
		if (m_Size + 1 == m_Capacity) {
			AllocateMem(m_Capacity + 5);
		}

		m_Data[m_Size++] = std::move(data);
	}

	template<typename ... Args>
	void EmplaceBack(const Args&... args) {
		AddRecur(args...);
	}

	template<typename ... Args>
	void Emplace(size_t index, const Args&... args) {
		if (index > m_Size) {
			throw std::exception();
		}

		EmplaceHelper(index, args...);
	}

	void PopBack() {
		if (m_Size != 0) {
			m_Data[--m_Size].~T();
		}
	}

	int Find(const T& searchElem) {
		int index = -1;

		for (unsigned int i = 0; i < m_Size; i++) {
			if (searchElem == m_Data[i]) {
				index = i;
				break;
			}
		}

		return index;
	}

	bool Remove(size_t index) {
		if (index >= m_Size) {
			return false;
		}

		for (unsigned int i = index; i < m_Size - 1; i++) {
			m_Data[i] = m_Data[i + 1];
		}

		m_Size--;
		return true;
	}

	void Insert(const T& data, size_t index) {
		if (index > m_Size) {
			throw std::exception();
		}

		if (m_Size + 1 == m_Capacity) {
			AllocateMem(m_Capacity + 5);
		}

		for (unsigned i = m_Size; i > index; i--) {
			m_Data[i] = m_Data[i - 1];
		}

		m_Data[index] = data;
		m_Size++;
	}

	void Insert(T&& data, size_t index) {
		if (index > m_Size) {
			throw std::exception();
		}

		if (m_Size + 1 == m_Capacity) {
			AllocateMem(m_Capacity + 5);
		}

		for (unsigned i = m_Size; i >= index; i--) { //Start backwards to avoid overwriting data
			m_Data[i] = std::move(m_Data[i - 1]);
		}

		m_Data[index] = data;
		m_Size++;
	}

	const T& At(size_t index) const {
		if (index >= m_Size) {
			throw std::exception();
		}

		return m_Data[index];
	}

	inline size_t capacity() const { return m_Capacity; }
	inline size_t size() const { return m_Size; }
	inline bool isEmpty() const { return m_Size == 0; }

	const T& operator[](size_t index) const {
		if (index >= m_Size) {
			throw std::exception();
		}

		return m_Data[index];
	}

	T& operator[](size_t index) {
		if (index >= m_Size) {
			throw std::exception();
		}

		return m_Data[index];
	}

private:
	void AllocateMem(size_t newSize) {
		m_Capacity = newSize;
		T * tempData = new T[m_Capacity];

		for (size_t i = 0; i < m_Size; i++) { //Copy data onto temp vector with the newly allocated space
			tempData[i] = m_Data[i];
		}

		delete[] m_Data;
		m_Data = tempData;
	}

	template<typename ... Args>
	void AddRecur(const T& currentData, const Args&... args) {
		PushBack(currentData);
		AddRecur(args...);
	}

	template<typename ... Args>
	void AddRecur(const T& lastData) {
		PushBack(lastData);
	}

	template<typename ... Args>
	void EmplaceHelper(size_t currentIndex, const T& data, const Args&... args) {
		Insert(data, currentIndex);
		EmplaceHelper(currentIndex + 1, args...);
	}

	template<typename ... Args>
	void EmplaceHelper(size_t currentIndex, const T& data) {
		Insert(data, currentIndex);
	}

	T * m_Data = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;
};