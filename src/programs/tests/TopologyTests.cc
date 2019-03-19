
#include "catch.hpp"
#include <greenfield/Topology.h>
#include "TopologyTestFixtures.h"


namespace greenfield {

    TEST_CASE("greenfield::Topology: Basic functionality") {

        Topology topology;

        auto q0 = new Queue<int>;
        auto q1 = new Queue<double>;

        topology.addQueue(q0);
        topology.addQueue(q1);

        topology.addArrow("emit_rand_ints", new RandIntSourceArrow(q0));
        topology.addArrow("multiply_by_two", new MultByTwoArrow(q0, q1));
        topology.addArrow("sum_everything", new SumArrow<double>(q1));
    }
}