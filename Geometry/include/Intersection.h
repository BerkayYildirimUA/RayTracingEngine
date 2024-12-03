//
// Created by berka on 08/10/2024.
//

#ifndef RAYTRACINGENGINE_INTERSECTION_H
#define RAYTRACINGENGINE_INTERSECTION_H

#include <vector>
#include <memory>
#include "Core/include/Ray.h"
#include "iostream"
#include <string>
#include "HitInfo.h"

class Intersection {
private:
    std::vector<std::unique_ptr<HitInfo>> hits;

public:
    int numHits = 0;
    std::vector<Ray> secondaryRays;

    explicit Intersection(int numHits);
    Intersection();

    void set(Intersection& intersection);
    std::unique_ptr<HitInfo> &getHit(int i);
    [[nodiscard]] const std::unique_ptr<HitInfo> &getHit(int i) const;

    const std::vector<std::unique_ptr<HitInfo>> &getHits() const;


    void resize(int size);

    auto begin();
    auto end();

    [[nodiscard]] auto begin() const;
    [[nodiscard]] auto end() const;


};


#endif //RAYTRACINGENGINE_INTERSECTION_H


/*
template <typename T>
class TrackedUniquePtr {
private:
    std::unique_ptr<T> ptr;
    std::string owner;

public:
    TrackedUniquePtr(T* rawPtr = nullptr, const std::string& ownerName = "Unknown")
            : ptr(rawPtr), owner(ownerName) {}

    // Transfer ownership
    TrackedUniquePtr(TrackedUniquePtr&& other) noexcept
            : ptr(std::move(other.ptr)), owner(std::move(other.owner)) {
        other.owner.clear();
    }

    TrackedUniquePtr& operator=(TrackedUniquePtr&& other) noexcept {
        if (this != &other) {
            ptr = std::move(other.ptr);
            owner = std::move(other.owner);
            other.owner.clear();
        }
        return *this;
    }

    // Accessors
    T* get() const { return ptr.get(); }
    const std::string& getOwner() const { return owner; }
    void setOwner(const std::string& newOwner) { owner = newOwner; }

    T* operator->() const { return ptr.get(); }
    T& operator*() const { return *ptr; }

    explicit operator bool() const { return ptr != nullptr; }

    ~TrackedUniquePtr() {
        if (ptr) {
            std::cout << "TrackedUniquePtr owned by " << owner << " destroyed resource at " << ptr.get() << "\n";
        }
    }
};*/