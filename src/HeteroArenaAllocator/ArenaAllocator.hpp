#pragma once
#include "Arena.hpp"

class ArenaAllocator {
public:
	ArenaAllocator(Arena &arena)
	: _arena(arena) {}

	// returns a pointer to storage aligned and sized for n elements of type T
	template<typename T>
	auto allocate(size_t n = 1) -> void*;

	// allocates and in-place constructs a T object and returns a pointer to it
	template<typename T, typename ...Args>
	auto construct(Args&& ...args)->T*;

private:
	Arena& _arena;
};

template<typename T>
auto ArenaAllocator::allocate(size_t n) -> void* {
	uint8_t* pastTheEnd = _arena._getStorage() + _arena._getSize();

	size_t requested_size = n * sizeof(T);
	auto& waterlineRef = _arena._getWaterline();
	auto& waterlineRawRef = reinterpret_cast<void*&>(waterlineRef);
	size_t capacity = pastTheEnd - waterlineRef;

	void* storage = std::align(alignof(T), requested_size, waterlineRawRef, capacity);
	if (storage != nullptr) {
		waterlineRef = reinterpret_cast<uint8_t*>(storage) + requested_size;
		return storage;
	}
	return nullptr;
}

template<typename T, typename ...Args>
auto ArenaAllocator::construct(Args&& ...args) -> T* {
	void* storage = allocate<T>();
	if (!storage) { return nullptr; }

	return new(storage) T(std::forward<Args>(args)...);
}
