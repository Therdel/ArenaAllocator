#include <iostream>
#include "ArenaAllocator.hpp"

auto useStackArena() {
	StackArena<sizeof(int)> stackArena;
	ArenaAllocator allocator(stackArena);

	auto* ptr = allocator.construct<int>(1337);
	if (ptr == nullptr) {
		throw std::bad_alloc();
	}

	std::cout << "Stack arena-allocated value: " << *ptr << std::endl;
}

auto useHeapArena() {
	HeapArena heapArena(sizeof(int));
	ArenaAllocator allocator(heapArena);

	auto* ptr = allocator.construct<int>(420);
	if (ptr == nullptr) {
		throw std::bad_alloc();
	}

	std::cout << "Heap arena-allocated value: " << *ptr << std::endl;
}

int main() {
	useStackArena();
	useHeapArena();
}