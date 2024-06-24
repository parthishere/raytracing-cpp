#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable {
    public:
        std::vector<std::shared_ptr<Hittable>> objects;

        HittableList() {}
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear() {objects.clear();}

        void add(std::shared_ptr<Hittable> object){
            objects.push_back(object);
        } 

        bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override{
            HitRecord temp_record;
            bool hit_anything = false;
            double closest_point_of_intersection = ray_t.max;

            for(const std::shared_ptr<Hittable>& object : objects){
                if(object->hit(ray, Interval(ray_t.min, closest_point_of_intersection), temp_record)){
                    hit_anything = true;
                    closest_point_of_intersection = temp_record.distance;
                    record = temp_record;
                }
            }

            return hit_anything;
        }
    private:
};


#endif