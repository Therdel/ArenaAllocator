#pragma once
#include <memory>	// std::unique_ptr
#include <cstddef>	// std::max_align_t

class Arena {
public:
    virtual ~Arena() noexcept = default;

private:
	friend class ArenaAllocator;

	// pointer to beginning of the arena storage
	virtual auto _getStorage()-> uint8_t* = 0;

	// total size of the arena
	virtual auto _getSize()-> size_t = 0;

	// pointer to unallocated/free half of arena
	virtual auto _getWaterline()-> uint8_t*& = 0;
};

template <size_t size, size_t alignment = alignof(std::max_align_t)>
class StackArena final : public Arena {
public:
	StackArena()
	: _storage{}
	, _waterline{ _storage } {}

private:
	alignas(alignment) uint8_t _storage[size];
	uint8_t* _waterline;

	auto _getStorage() -> uint8_t* override { return _storage; }
	auto _getSize() -> size_t override { return size; }
	auto _getWaterline() -> uint8_t*& override { return _waterline; }
};

class HeapArena final : public Arena {
public:
	HeapArena(size_t size)
	: _storage(std::make_unique<uint8_t[]>(size))
	, _size(size)
	, _waterline(_storage.get()) {}

private:
	std::unique_ptr<uint8_t[]> _storage;
	size_t _size;
	uint8_t* _waterline;

	auto _getStorage() -> uint8_t* override { return _storage.get(); }
	auto _getSize() -> size_t override { return _size; }
	auto _getWaterline() -> uint8_t*& override { return _waterline; }
};
