#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <cstdint>
#include <fstream>

#include "creature.hpp"

class PopulationLogger {
    public:
        PopulationLogger(std::vector<Creature>& creatures) {
            getInitialCounts(creatures);
            outputPops();
        }
        uint32_t num_prey = 0;
        uint32_t num_pred = 0;
        uint32_t epoch = 0;
        void outputPops() {
            std::ofstream pop_data;
            pop_data.open("../data.dat", std::ios_base::app);
            pop_data << num_prey << " " << num_pred << " " << epoch << std::endl;
            ++epoch;
            pop_data.close();
        }
    private:
        void getInitialCounts(std::vector<Creature>& creatures) {
            for (auto& creature : creatures) {
                if (creature.getType() == CreatureType::Predator)
                    ++num_pred;
                else if (creature.getType() == CreatureType::Prey)
                    ++num_prey;
            }
        }
};

#endif
