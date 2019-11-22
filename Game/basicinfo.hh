#ifndef BASICINFO_HH
#define BASICINFO_HH

#include "core/basicresources.h"
#include <vector>
#include <QDebug>

Course::ResourceMap fixedResourceMultiplier(const Course::ResourceMap& resources, const Course::ResourceMapDouble& multiplier);

// PLAYERS //

const Course::ResourceMap PLAYER_STARTING_RESOURCES = {
    {Course::BasicResource::NONE, 0},
    {Course::BasicResource::MONEY, 1000},
    {Course::BasicResource::FOOD, 600},
    {Course::BasicResource::WOOD, 400},
    {Course::BasicResource::STONE, 200},
    {Course::BasicResource::ORE, 0}
};

// BUILDINGS //

const std::vector<Course::ResourceMap> HQ_BUILD_COST_LIST = {
    {
        {Course::BasicResource::MONEY, 1000},
        {Course::BasicResource::FOOD, 1000},
        {Course::BasicResource::WOOD, 1000},
        {Course::BasicResource::STONE, 1000},
        {Course::BasicResource::ORE, 1000}
    }
};

const std::vector<Course::ResourceMap> HQ_PRODUCTION_LIST = {
    { }
};

const std::vector<Course::ResourceMap> OUTPOST_BUILD_COST_LIST = {
    {
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::STONE, 100}
    },
    {
        {Course::BasicResource::MONEY, 400},
        {Course::BasicResource::ORE, 100}
    }
};


const std::vector<Course::ResourceMap> OUTPOST_PRODUCTION_LIST = {
    { },
    { },
    { }
};

const std::vector<Course::ResourceMap> CAMPUS_BUILD_COST_LIST = {
    {
        {Course::BasicResource::MONEY, 1000},
        {Course::BasicResource::FOOD, 1000},
        {Course::BasicResource::WOOD, 1000},
        {Course::BasicResource::STONE, 1000},
        {Course::BasicResource::ORE, 1000}
    }
};

const std::vector<Course::ResourceMap> CAMPUS_PRODUCTION_LIST = {
    { }
};

const std::vector<Course::ResourceMap> FISHERY_BUILD_COST_LIST = {
    {
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::STONE, 100}
    },
    {
        {Course::BasicResource::MONEY, 400},
        {Course::BasicResource::ORE, 100}
    }
};


const std::vector<Course::ResourceMap> FISHERY_PRODUCTION_LIST = {
    {
        {Course::BasicResource::FOOD, 10}
    },
    {
        {Course::BasicResource::FOOD, 30}
    },
    {
        {Course::BasicResource::FOOD, 70}
    }
};

const std::vector<Course::ResourceMap> MARKET_BUILD_COST_LIST = {
    {
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::STONE, 100}
    },
    {
        {Course::BasicResource::MONEY, 400},
        {Course::BasicResource::ORE, 100}
    }
};

const std::vector<Course::ResourceMap> MARKET_PRODUCTION_LIST = {
    {
        {Course::BasicResource::MONEY, 10}
    },
    {
        {Course::BasicResource::MONEY, 30}
    },
    {
        {Course::BasicResource::MONEY, 70}
    }
};

const std::vector<Course::ResourceMap> MINE_BUILD_COST_LIST = {
    {
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::STONE, 100}
    },
    {
        {Course::BasicResource::MONEY, 400},
        {Course::BasicResource::ORE, 100}
    }
};

const std::vector<Course::ResourceMap> MINE_PRODUCTION_LIST {
    {
        {Course::BasicResource::STONE, 10},
        {Course::BasicResource::ORE, 5}
    },
    {
        {Course::BasicResource::STONE, 20},
        {Course::BasicResource::ORE, 35}
    },
    {
        {Course::BasicResource::STONE, 40},
        {Course::BasicResource::ORE, 75}
    }
};

const std::vector<Course::ResourceMap> RANCH_BUILD_COST_LIST = {
    {
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::STONE, 100}
    },
    {
        {Course::BasicResource::MONEY, 400},
        {Course::BasicResource::ORE, 100}
    }
};

const std::vector<Course::ResourceMap> RANCH_PRODUCTION_LIST = {
    {
        {Course::BasicResource::FOOD, 10}
    },
    {
        {Course::BasicResource::FOOD, 30}
    },
    {
        {Course::BasicResource::FOOD, 70}
    }
};

const std::vector<Course::ResourceMap> SAWMILL_BUILD_COST_LIST =  {
    {
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::STONE, 100}
    },
    {
        {Course::BasicResource::MONEY, 400},
        {Course::BasicResource::ORE, 100}
    }
};

const std::vector<Course::ResourceMap> SAWMILL_PRODUCTION_LIST = {
    {
        {Course::BasicResource::WOOD, 10}
    },
    {
        {Course::BasicResource::WOOD, 30}
    },
    {
        {Course::BasicResource::WOOD, 70}
    }
};

// WORKERS //

const Course::ResourceMap BASIC_WORKER_BUILD_COST = {
    {Course::BasicResource::FOOD, 100}
};

const Course::ResourceMapDouble BASIC_WORKER_EFFICIENCY = {
    {Course::BasicResource::MONEY, 1.0},
    {Course::BasicResource::FOOD, 1.0},
    {Course::BasicResource::WOOD, 1.0},
    {Course::BasicResource::STONE, 1.0},
    {Course::BasicResource::ORE, 1.0}
};

const Course::ResourceMap SCOUT_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100}
};

const Course::ResourceMapDouble SCOUT_EFFICIENCY = {
    {Course::BasicResource::MONEY, 0.0},
    {Course::BasicResource::FOOD, 0.0},
    {Course::BasicResource::WOOD, 0.0},
    {Course::BasicResource::STONE, 0.0},
    {Course::BasicResource::ORE, 0.0}
};

// TILE RESOURCES //

const Course::ResourceMap FOREST_PROD = {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 2},
    {Course::BasicResource::WOOD, 10},
    {Course::BasicResource::STONE, 1},
    {Course::BasicResource::ORE, 0},
};

const Course::ResourceMap GRASSLAND_PROD = {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 10},
    {Course::BasicResource::WOOD, 2},
    {Course::BasicResource::STONE, 1},
    {Course::BasicResource::ORE, 0},
};

const Course::ResourceMap SAND_PROD = {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 2},
    {Course::BasicResource::ORE, 0},
};

const Course::ResourceMap STONE_PROD = {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 10},
    {Course::BasicResource::ORE, 5},
};

const Course::ResourceMap SWAMP_PROD = {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 2},
    {Course::BasicResource::WOOD, 1},
    {Course::BasicResource::STONE, 1},
    {Course::BasicResource::ORE, 0},
};

const Course::ResourceMap WATER_PROD = {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 10},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0},
};

// TILE BUILDABLE BUILDINGS //
const std::vector<std::string> FOREST_BUILD {
    {"HeadQuarters"},
    {"Outpost"},
    {"Sawmill"}
};

const std::vector<std::string> GRASSLAND_BUILD {
    {"HeadQuarters"},
    {"Outpost"},
    {"Market"},
    {"Campus"},
    {"Farm"}
};

const std::vector<std::string> SAND_BUILD {
    {"HeadQuarters"},
    {"Outpost"},
    {"Market"},
    {"Campus"}
};

const std::vector<std::string> STONE_BUILD {
    {"HeadQuarters"},
    {"Outpost"},
    {"Mine"}
};

const std::vector<std::string> SWAMP_BUILD {
    {"HeadQuarters"},
    {"Outpost"}
};

const std::vector<std::string> WATER_BUILD {
    {"Fishery"}
};

const Course::ResourceMapDouble NEGATIVE {
    {Course::BasicResource::NONE, -1},
    {Course::BasicResource::MONEY, -1},
    {Course::BasicResource::FOOD, -1},
    {Course::BasicResource::WOOD, -1},
    {Course::BasicResource::STONE, -1},
    {Course::BasicResource::ORE, -1}
};

const Course::ResourceMapDouble HALF {
    {Course::BasicResource::NONE, 0.5},
    {Course::BasicResource::MONEY, 0.5},
    {Course::BasicResource::FOOD, 0.5},
    {Course::BasicResource::WOOD, 0.5},
    {Course::BasicResource::STONE, 0.5},
    {Course::BasicResource::ORE, 0.5}
};

const Course::ResourceMapDouble ZERO {
    {Course::BasicResource::NONE, 0},
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0},
    {Course::BasicResource::ORE, 0}
};

#endif // BASICINFO_HH
