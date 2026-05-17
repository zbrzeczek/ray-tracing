struct Vec3
{
    float x, y, z;

    Vec3 operator+(const Vec3& r) {
        return {x + r.x, y + r.y, z+ r.z};
    }
    Vec3 operator-(const Vec3& r) {
        return {x - r.x, y - r.y, z - r.z};
    }
    Vec3 operator*(const Vec3& r) {
        return {x * r.x, y * r.y, z * r.z};
    }
    

    // TODO dodaj tutaj
    // - dot operation
    // - normalization 
};
