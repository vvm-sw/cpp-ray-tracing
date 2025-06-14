#include "Point.h"
#include "Operations.h"
#include "Vector.h"
#include "Hittable.h"

class Plane : public Hittable {
private:
    Point planePoint;
    Vector normal;
    Vector color;

public:
    // Constructor
    Plane(Point newPlanePoint, Vector newNormal, Vector newColor);

    // Getters
    Point getPlanePoint() const;
    Vector getNormal() const;
    Vector getColor() const;
    
    // Setters
    void setPlanePoint(Point& planePoint);
    void setNormal(Vector& normal);
    void setColor(Vector& color);

    // Hit
    virtual bool hit(const Ray& ray) const override;
};


