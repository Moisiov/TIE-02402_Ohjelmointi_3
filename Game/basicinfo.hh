#ifndef BASICINFO_HH
#define BASICINFO_HH

#include "core/basicresources.h"
#include <vector>

// PLAYERS //

const Course::ResourceMap PLAYER_STARTING_RESOURCES = {
    {Course::BasicResource::NONE, 0},
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 100},
    {Course::BasicResource::STONE, 100},
    {Course::BasicResource::ORE, 100}
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
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100},
        {Course::BasicResource::STONE, 100},
        {Course::BasicResource::ORE, 100}
    }
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
  {} // Intentionally empty, no production
};

const std::vector<Course::ResourceMap> FISHERY_BUILD_COST_LIST = {
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    }
};


const std::vector<Course::ResourceMap> FISHERY_PRODUCTION_LIST = {
    {
        {Course::BasicResource::MONEY, 5},
        {Course::BasicResource::FOOD, 10}
    },
    {
        {Course::BasicResource::MONEY, 10},
        {Course::BasicResource::FOOD, 20}
    },
    {
        {Course::BasicResource::MONEY, 15},
        {Course::BasicResource::FOOD, 30}
    }
};

const std::vector<Course::ResourceMap> MARKET_BUILD_COST_LIST = {
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    }
};

const std::vector<Course::ResourceMap> MARKET_PRODUCTION_LIST = {
    {
        {Course::BasicResource::MONEY, 10}
    },
    {
        {Course::BasicResource::MONEY, 20}
    },
    {
        {Course::BasicResource::MONEY, 30}
    }
};

const std::vector<Course::ResourceMap> MINE_BUILD_COST_LIST = {
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    }
};

const std::vector<Course::ResourceMap> MINE_PRODUCTION_LIST {
    {
        {Course::BasicResource::STONE, 10},
        {Course::BasicResource::ORE, 5}
    },
    {
        {Course::BasicResource::STONE, 20},
        {Course::BasicResource::ORE, 10}
    },
    {
        {Course::BasicResource::STONE, 30},
        {Course::BasicResource::ORE, 15}
    }
};

const std::vector<Course::ResourceMap> RANCH_BUILD_COST_LIST = {
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    }
};

const std::vector<Course::ResourceMap> RANCH_PRODUCTION_LIST = {
    {
        {Course::BasicResource::FOOD, 10}
    },
    {
        {Course::BasicResource::FOOD, 20}
    },
    {
        {Course::BasicResource::FOOD, 30}
    }
};

const std::vector<Course::ResourceMap> SAWMILL_BUILD_COST_LIST =  {
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    }
};

const std::vector<Course::ResourceMap> SAWMILL_PRODUCTION_LIST = {
    {
        {Course::BasicResource::MONEY, 5},
        {Course::BasicResource::WOOD, 10}
    },
    {
        {Course::BasicResource::MONEY, 10},
        {Course::BasicResource::WOOD, 20}
    },
    {
        {Course::BasicResource::MONEY, 15},
        {Course::BasicResource::WOOD, 30}
    }
};

// WORKERS //

const Course::ResourceMap BASIC_WORKER_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 100}
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
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 100}
};

const Course::ResourceMapDouble SCOUT_EFFICIENCY = {
    {Course::BasicResource::MONEY, 0.0},
    {Course::BasicResource::FOOD, 0.0},
    {Course::BasicResource::WOOD, 0.0},
    {Course::BasicResource::STONE, 0.0},
    {Course::BasicResource::ORE, 0.0}
};

#endif // BASICINFO_HH