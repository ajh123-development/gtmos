/*
    This file is part of duckOS.
    
    duckOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    duckOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with duckOS.  If not, see <https://www.gnu.org/licenses/>.
    
    Copyright (c) Byteduck 2016-2020. All rights reserved.
*/

#include "MemoryMap.h"
#include "MemoryRegion.h"
#include "PageDirectory.h"
#include <kernel/tasking/Thread.h>
#include <kernel/KernelMapper.h>

MemoryMap::MemoryMap(size_t page_size, MemoryRegion *first_region): _page_size(page_size), _first_region(first_region) {
	if(first_region) {
		MemoryRegion* cur = _first_region;
		while(cur->next) {
			cur = cur->next;
		}
		_last_region = cur;
	}
}

MemoryMap::~MemoryMap() {
	MemoryRegion* cur = _first_region;
	while(cur) {
		MemoryRegion* next = cur->next;
		if(cur->heap_allocated)
			delete cur->prev;
		cur = next;
	}
}

MemoryRegion* MemoryMap::allocate_region(size_t minimum_size, MemoryRegion* storage) {
	if(minimum_size == 0) return nullptr;

	bool alloced_storage = !storage;
	if(alloced_storage)
		storage = new MemoryRegion();

	lock.acquire();

	MemoryRegion* cur = _first_region;
	//Round size up to be a multiple of the page size
	size_t size = ((minimum_size + _page_size - 1) / _page_size) * _page_size;
	while(cur) {
		//If the current region is smaller than the requested size or is used, move on
		if(cur->used || cur->size < size) {
			cur = cur->next;
			continue;
		}

		//If the current region is the same size as the requested size, just mark it as used and return
		bytes_used += size;
		if(cur->size == size) {
			cur->used = true;
			lock.release();
			if(alloced_storage)
				delete storage;
			return cur;
		}

		//Make a new memory region after the current region and insert it into the linked list
		*storage = MemoryRegion(cur->start + size, cur->size - size);
		storage->prev = cur;
		storage->next = cur->next;
		if(cur->next)
			cur->next->prev = storage;
		else
			_last_region = storage;
		cur->next = storage;
		cur->size = size;
		cur->used = true;

		lock.release();

		return cur;
	}

	lock.release();

	if(alloced_storage)
		delete storage;

	return nullptr;
}

MemoryRegion* MemoryMap::allocate_stack_region(size_t minimum_size, MemoryRegion* storage) {
	if(minimum_size == 0) return nullptr;

	bool alloced_storage = !storage;
	if(alloced_storage)
		storage = new MemoryRegion();

	lock.acquire();

	MemoryRegion* cur = _last_region;
	//Round size up to be a multiple of the page size
	size_t size = ((minimum_size + _page_size - 1) / _page_size) * _page_size;
	while(cur) {
		//If the current region is smaller than the requested size or is used, move on
		if(cur->used || cur->size < size) {
			cur = cur->prev;
			continue;
		}

		//If the current region is the same size as the requested size, just mark it as used and return
		bytes_used += size;
		if(cur->size == size) {
			cur->used = true;
			lock.release();
			if(alloced_storage)
				delete storage;
			return cur;
		}

		//Make a new memory region before the current region and insert it into the linked list
		*storage = MemoryRegion(cur->start, cur->size - size);
		storage->prev = cur->prev;
		storage->next = cur;
		if(cur->prev)
			cur->prev->next = storage;
		else
			_first_region = storage;
		cur->prev = storage;
		cur->start = storage->start + storage->size;
		cur->size = size;
		cur->used = true;

		lock.release();

		return cur;
	}

	lock.release();

	if(alloced_storage)
		delete storage;

	return nullptr;
}

MemoryRegion* MemoryMap::allocate_region(size_t address, size_t minimum_size, MemoryRegion* storage_a, MemoryRegion* storage_b) {
	if(minimum_size == 0) return nullptr;

	bool alloced_storage_a = !storage_a;
	if(alloced_storage_a)
		storage_a = new MemoryRegion();

	bool alloced_storage_b = !storage_b;
	if(alloced_storage_b)
		storage_b = new MemoryRegion();

	lock.acquire();

	MemoryRegion* cur = _first_region;
	//Round size up to be a multiple of the page size
	size_t address_pagealigned = (address / _page_size) * _page_size;
	size_t size = (((minimum_size + (address - address_pagealigned)) + _page_size - 1) / _page_size) * _page_size;
	while(cur) {
		//If the current region doesn't contain the address, move on
		if(cur->start + cur->size <= address_pagealigned) {
			cur = cur->next;
			continue;
		}

		//If the current region is past the address or is not big enough, return nullptr
		if(cur->start > address_pagealigned || (cur->start + cur->size) < (address_pagealigned + size)) {
			lock.release();

			if(alloced_storage_a)
				delete storage_a;
			if(alloced_storage_b)
				delete storage_b;

			return nullptr;
		}

		//If the current region is used, return nullptr
		if(cur->used) {
			lock.release();

			if(alloced_storage_a)
				delete storage_a;
			if(alloced_storage_b)
				delete storage_b;

			return nullptr;
		}

		bytes_used += size;

		//If the current region is the same size as the requested size, just mark it as used and return
		if(cur->start == address_pagealigned && cur->size == size) {
			cur->used = true;
			lock.release();
			return cur;
		}

		cur->used = true;

		//Create a new region after cur (if necessary), and then update the linked list
		size_t size_after = (cur->start + cur->size) - (address_pagealigned + size);
		if(size_after) {
			*storage_a = MemoryRegion(address + size, size_after);
			if (cur->next)
				cur->next->prev = storage_a;
			else
				_last_region = storage_a;
			storage_a->next = cur->next;
			storage_a->prev = cur;
			cur->next = storage_a;
		} else if(alloced_storage_a) {
			delete storage_a;
		}

		//Create a new region before cur (if necessary) and update the linked list
		if(cur->start != address_pagealigned) {
			*storage_b = MemoryRegion(cur->start, address_pagealigned - cur->start);
			if (cur->prev)
				cur->prev->next = storage_b;
			storage_b->prev = cur->prev;
			storage_b->next = cur;
			cur->prev = storage_b;
			cur->start += storage_b->size;
			if(cur == _first_region)
				_first_region = storage_b;
		} else if(alloced_storage_b) {
			delete storage_b;
		}

		cur->size = size;

		lock.release();

		return cur;
	}

	lock.release();

	if(alloced_storage_a)
		delete storage_a;
	if(alloced_storage_b)
		delete storage_b;

	return nullptr;
}

void MemoryMap::free_region(MemoryRegion *region) {
	if(!region->used) return;

	lock.acquire();

	region->free();
	bytes_used -= region->size;

	//If the previous region is also free and continuous with this one, merge them
	if(region->prev && !region->prev->used && region->prev->start + region->prev->size == region->start) {
		region->start = region->prev->start;
		region->size += region->prev->size;
		if(region->prev->prev)
			region->prev->prev->next = region;
		MemoryRegion* old_prev = region->prev;
		region->prev = region->prev->prev;
		if(old_prev->heap_allocated)
			delete old_prev;
		if(old_prev == _first_region)
			_first_region = region;
	}

	//If the next region is also free and continuous with this one, merge them
	if(region->next && !region->next->used && region->next->start == region->start + region->size) {
		region->size += region->next->size;
		if(region->next->next)
			region->next->next->prev = region;
		MemoryRegion* old_next = region->next;
		region->next = region->next->next;
		if(old_next->heap_allocated)
			delete old_next;
		if(old_next == _last_region)
			_last_region = region;
	}

	lock.release();
}

MemoryRegion* MemoryMap::split_region(MemoryRegion* region, size_t split_start, size_t split_size) {
	if(split_start < region->start) return nullptr;
	size_t split_end = split_start + split_size - 1;
	if(split_end >= region->start + region->size) return nullptr;

	lock.acquire();

	//Create a new region before split_start if necessary and update the linked list
	if(split_start != region->start) {
		auto* new_region = new MemoryRegion(region->start, split_start - region->start);
		if (region->prev)
			region->prev->next = new_region;
		new_region->prev = region->prev;
		new_region->next = region;
		region->prev = new_region;
		if(region == _first_region)
			_first_region = new_region;
	}

	//Create a new region after split_end if necessary
	if(split_end != region->start + region->size - 1) {
		auto* new_region = new MemoryRegion(split_start + split_size, (region->start + region->size) - split_end);
		if (region->next)
			region->next->prev = new_region;
		new_region->next = region->next;
		new_region->prev = region;
		region->next = new_region;
		if(region == _last_region)
			_last_region = new_region;
	}

	//Update the region's start and size
	region->start = split_start;
	region->size = split_size;

	lock.release();

	return region;
}

size_t MemoryMap::page_size() {
	return _page_size;
}

MemoryRegion *MemoryMap::first_region() {
	return _first_region;
}

size_t MemoryMap::used_memory() {
	return bytes_used;
}

size_t MemoryMap::reserved_memory() {
	return bytes_reserved;
}

MemoryRegion *MemoryMap::find_region(size_t address) {
	lock.acquire();
	MemoryRegion* cur = _first_region;
	while(cur) {
		if(address >= cur->start && cur->start + cur->size > address) {
			lock.release();
			return cur;
		}
		cur = cur->next;
	}
	lock.release();
	return nullptr;
}

MemoryRegion *MemoryMap::find_shared_region(int id) {
	lock.acquire();
	MemoryRegion* cur = _first_region;
	while(cur) {
		if(cur->is_shm && cur->shm_id == id) {
			lock.release();
			return cur;
		}
		cur = cur->next;
	}
	lock.release();
	return nullptr;
}


void MemoryMap::replace_entry(MemoryRegion *old_region, MemoryRegion *new_region) {
	lock.acquire();
	if(old_region->next)
		old_region->next->prev = new_region;
	if(old_region->prev)
		old_region->prev->next = new_region;
	if(old_region->related && old_region->related->related == old_region)
		old_region->related->related = new_region;
	new_region->next = old_region->next;
	new_region->prev = old_region->prev;
	if(old_region == _first_region)
		_first_region = new_region;
	if(old_region == _last_region)
		_last_region = new_region;
	lock.release();
}

void MemoryMap::recalculate_memory_totals() {
	lock.acquire();
	bytes_used = 0;
	bytes_reserved = 0;
	MemoryRegion* cur = _first_region;
	while(cur) {
		bytes_used += cur->used && !cur->reserved ? cur->size : 0;
		bytes_reserved += cur->reserved ? cur->size : 0;
		cur = cur->next;
	}
	lock.release();
}
