#pragma once
#include <Windows.h>
#include <Psapi.h>

#include <vector>
#include <string>

#include <filesystem>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <functional>
#include <random>
#include <chrono>

#include <map>

#include <MinHook.h>

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

#define PI 3.14159265359

struct Vec2 {
	union {
		struct {
			float x, y;
		};
		float arr[2];
	};

	Vec2() { x = y = 0; }
	Vec2(float x = 0, float y = 0) {
		this->x = x, this->y = y;
	}

	bool operator == (Vec2 v) { return v.x == x && v.y == y; };
	bool operator != (Vec2 v) { return v.x != x || v.y != y; };

	/* Add */

	Vec2 add(float f) {
		return Vec2(x + f, y + f);
	}

	Vec2 add(float a, float b) {
		return Vec2(x + a, y + b);
	}

	Vec2 add(Vec2 o) {
		return Vec2(x + o.y, y + o.y);
	}

	/* Subtract */

	Vec2 sub(float f) {
		return Vec2(x - f, y - f);
	}

	Vec2 sub(float a, float b) {
		return Vec2(x - a, x - b);
	}

	Vec2 sub(Vec2 o) {
		return Vec2(x - o.x, y - o.y);
	}

	/* Divide */

	Vec2 div(float f) {
		return Vec2(x / f, y / f);
	}

	Vec2 div(float a, float b) {
		return Vec2(x / a, y / b);
	}

	Vec2 div(Vec2 o) {
		return Vec2(x / o.x, y / o.y);
	}

	/* Multiply */

	Vec2 mult(float f) {
		return Vec2(x * f, y * f);
	}

	Vec2 mult(float a, float b) {
		return Vec2(x * a, y * b);
	}

	Vec2 mult(Vec2 o) {
		return Vec2(x * o.x, y * o.y);
	}

	/* Other */

	int distance(Vec2 o) {
		int dX = x - o.y;
		int dY = y - o.y;
		return sqrt(dX * dX + dY * dY);
	}
};

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float arr[3];
	};

	Vec3() { x = y = z = 0; }
	Vec3(float x = 0, float y = 0, float z = 0) {
		this->x = x, this->y = y, this->z = z;
	}

	bool operator == (Vec3 v) { return v.x == x && v.y == y && v.z == z; };
	bool operator != (Vec3 v) { return v.x != x || v.y != y || v.z != z; };

	/* Add */

	Vec3 add(float f) {
		return Vec3(x + f, y + f, z + f);
	}

	Vec3 add(float a, float b, float c) {
		return Vec3(x + a, y + b, z + c);
	}

	Vec3 add(Vec3 o) {
		return Vec3(x + o.y, y + o.y, z + o.z);
	}

	/* Subtract */

	Vec3 sub(float f) {
		return Vec3(x - f, y - f, z - f);
	}

	Vec3 sub(float a, float b, float c) {
		return Vec3(x - a, x - b, z - c);
	}

	Vec3 sub(Vec3 o) {
		return Vec3(x - o.x, y - o.y, z - o.z);
	}

	/* Divide */

	Vec3 div(float f) {
		return Vec3(x / f, y / f, z / f);
	}

	Vec3 div(float a, float b, float c) {
		return Vec3(x / a, y / b, z / c);
	}

	Vec3 div(Vec3 o) {
		return Vec3(x / o.x, y / o.y, z / o.y);
	}

	/* Multiply */

	Vec3 mult(float f) {
		return Vec3(x * f, y * f, z * f);
	}

	Vec3 mult(float a, float b, float c) {
		return Vec3(x * a, y * b, z * c);
	}

	Vec3 mult(Vec3 o) {
		return Vec3(x * o.x, y * o.y, z * o.z);
	}

	/* Other */

	Vec3 floor() {
		return Vec3(floorf(x), floorf(y), floorf(z));
	}

	float magnitude() {
		return sqrtf(x * x + y * y + z * z);
	}

	float magnitudexy() {
		return sqrtf(x * x + y * y);
	}

	float magnitudexz() {
		return sqrtf(x * x + z * z);
	}

	Vec3 normalize() {
		return div(magnitude());
	};

	float distance(Vec3 o) {
		float dX = x - o.x;
		float dY = y - o.y;
		float dZ = z - o.z;
		return sqrt(dX * dX + dY * dY + dZ * dZ);
	}
};

struct Vec3_i {
	union {
		struct {
			int x, y, z;
		};
		int arr[3];
	};

	Vec3_i() { x = y = z = 0; }
	Vec3_i(int x = 0, int y = 0, int z = 0) {
		this->x = x, this->y = y, this->z = z;
	}

	bool operator == (Vec3_i v) { return v.x == x && v.y == y && v.z == z; };
	bool operator != (Vec3_i v) { return v.x != x || v.y != y || v.z != z; };

	/* Add */

	Vec3_i add(int i) {
		return Vec3_i(x + i, y + i, z + i);
	}

	Vec3_i add(int a, int b, int c) {
		return Vec3_i(x + a, y + b, z + c);
	}

	Vec3_i add(Vec3 o) {
		return Vec3_i(x + o.y, y + o.y, z + o.z);
	}

	/* Subtract */

	Vec3_i sub(int i) {
		return Vec3_i(x - i, y - i, z - i);
	}

	Vec3_i sub(int a, int b, int c) {
		return Vec3_i(x - a, x - b, z - c);
	}

	Vec3_i sub(Vec3 o) {
		return Vec3_i(x - o.x, y - o.y, z - o.z);
	}

	/* Divide */

	Vec3_i div(int i) {
		return Vec3_i(x / i, y / i, z / i);
	}

	Vec3_i div(int a, int b, int c) {
		return Vec3_i(x / a, y / b, z / c);
	}

	Vec3_i div(Vec3 o) {
		return Vec3_i(x / o.x, y / o.y, z / o.y);
	}

	/* Multiply */

	Vec3_i mult(int i) {
		return Vec3_i(x * i, y * i, z * i);
	}

	Vec3_i mult(int a, int b, int c) {
		return Vec3_i(x * a, y * b, z * c);
	}

	Vec3_i mult(Vec3 o) {
		return Vec3_i(x * o.x, y * o.y, z * o.z);
	}
};

struct Vec4 {
	union {
		struct {
			float x, y, z, w;
		};
		float arr[4];
	};
	Vec4() { x = y = z = w = 0; }
	Vec4(float x = 0, float y = 0, float z = 0, float w = 0) {
		this->x = x, this->y = y, this->z = z, this->w = w;
	}

	bool operator == (Vec4 v) { return v.x == x && v.y == y && v.z == z && v.w == w; };
	bool operator != (Vec4 v) { return v.x != x || v.y != y || v.z != z || v.w != w; };
};

struct MC_Colour {
	union {
		struct {
			float r, g, b, a;
		};
		float arr[4];
	};
	bool shouldDelete = true;

	MC_Colour() {
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	};

	MC_Colour(const MC_Colour& other) {
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		this->a = other.a;
		this->shouldDelete = other.shouldDelete;
	}

	MC_Colour(const float* arr) {
		this->arr[0] = arr[0];
		this->arr[1] = arr[1];
		this->arr[2] = arr[2];
		this->arr[3] = arr[3];
	};

	MC_Colour(const float r, const float g, const float b, const float a = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	};

	MC_Colour(const int r, const int g, const int b, const int a = 255) {
		this->r = r / 255.0f;
		this->g = g / 255.0f;
		this->b = b / 255.0f;
		this->a = a / 255.0f;
	};

	MC_Colour(const float r, const float g, const float b, const float a, const bool shouldDelete) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
		this->shouldDelete = shouldDelete;
	};

	bool operator == (MC_Colour colour) {
		return this->r == colour.r && this->g == colour.g && this->b == colour.b;
	};

	bool operator != (MC_Colour colour) {
		return this->r != colour.r || this->g != colour.g || this->b != colour.b;
	};
};

class Utils {
public:
	static HMODULE hModule;
	static bool hasExtension(std::string fileName);
	static bool doesPathExist(std::string);
	static void CreateDir(std::string);
	static void DeletePath(std::string);
	static void WriteToFile(std::string, std::string);
	static void DebugLogOutput(std::string);
	static uintptr_t FindAddr(uintptr_t, std::vector<unsigned int>);
	static uintptr_t FindSig(const char*);
	static std::string ptrToStr(uintptr_t);

	static std::map<uint64_t, bool> KeyMapping;
	static bool usingKey(uint64_t);
};

class RenderUtils {
private:
	static class MinecraftUIRenderContext* CachedContext;
	static class BitmapFont* CachedFont;
public:
	static void SetContext(class MinecraftUIRenderContext* Context, class BitmapFont* Font);
	static void FlushText();
	static float GetTextWidth(std::string text, float textSize);
	static void RenderText(std::string text, Vec2 textPos, MC_Colour colour, float textSize, float alpha);

	static void FillRectangle(Vec4 position, MC_Colour colour, float alpha);
	static void DrawRectangle(Vec4 position, MC_Colour colour, float alpha, float lineWidth);
};
