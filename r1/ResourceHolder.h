#pragma once
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <utility>
#include <iostream>

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename);
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

};
#include "ResourceHolder.inl"