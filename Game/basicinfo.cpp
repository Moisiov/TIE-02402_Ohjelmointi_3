#include "basicinfo.hh"

Course::ResourceMap fixedResourceMultiplier(const Course::ResourceMap& resources, const Course::ResourceMapDouble& multiplier)
{
    Course::ResourceMap total = resources;

    for (auto it = total.begin(); it != total.end(); ++it) {
        if (multiplier.find(it->first) != multiplier.end()) {
            total[it->first] = total[it->first] * multiplier.find(it->first)->second;
        }
    }

    return total;
}
