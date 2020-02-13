#pragma once

#include <memory>
#include <vector>

template <size_t size, size_t alignment = alignof(std::max_align_t)>
class Arena {
public:
	Arena();

	template<typename T>
	auto allocate() -> void*;

	template<typename T, typename ...Args>
	auto construct(Args&& ...args)->T*;

private:
	alignas(alignment) uint8_t _storage[size];
	uint8_t* _waterline;
};

template<size_t size, size_t alignment>
Arena<size, alignment>::Arena()
	: _storage{}
	, _waterline{ &_storage[0] } {
}

template<size_t size, size_t alignment>
template<typename T>
auto Arena<size, alignment>::allocate() -> void* {
	uint8_t* pastTheEnd = _storage + size;
	size_t capacity = pastTheEnd - _waterline;
	auto &waterlineRef = reinterpret_cast<void*&>(_waterline);
	void* storage = std::align(alignof(T), sizeof(T), waterlineRef, capacity);
	if (storage != nullptr) {
		_waterline = reinterpret_cast<uint8_t*>(storage) + sizeof(T);
		return storage;
	}
	return nullptr;
}

template<size_t size, size_t alignment>
template<typename T, typename ...Args>
auto Arena<size, alignment>::construct(Args&&... args)->T* {
	void* storage = allocate<T>();
	if (!storage) { return nullptr; }

	return new(storage) T(std::forward<Args>(args)...);
}

class HeapArena {
public:
	HeapArena(size_t size)
		: _storage(size)
		, _waterline(_storage.data()) {
	}

	template<typename T>
	auto allocate(size_t n=1) -> void*;

	template<typename T, typename ...Args>
	auto construct(Args&& ...args)->T*;

private:
	std::vector<uint8_t> _storage;
	uint8_t *_waterline;	
};

template<typename T>
auto HeapArena::allocate(size_t n) -> void* {
	uint8_t* pastTheEnd = _storage.data() + _storage.size();

	size_t storage_size = n * sizeof(T);
	auto& waterlineRef = reinterpret_cast<void*&>(_waterline);
	size_t capacity = pastTheEnd - _waterline;

	void* storage = std::align(alignof(T), storage_size, waterlineRef, capacity);
	if (storage != nullptr) {
		_waterline = reinterpret_cast<uint8_t*>(storage) + storage_size;
		return storage;
	}
	return nullptr;
}

template<typename T, typename ...Args>
auto HeapArena::construct(Args&&... args)->T* {
	void* storage = allocate<T>();
	if (!storage) { return nullptr; }

	return new(storage) T(std::forward<Args>(args)...);
}
