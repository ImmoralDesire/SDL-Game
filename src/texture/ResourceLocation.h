#ifndef RESOURCELOCATION_H
#define RESOURCELOCATION_H

class ResourceLocation {
public:
	const char* file;

	ResourceLocation(const char* a) : file(a) {}
	virtual ~ResourceLocation() {}
};

#endif
