//
// Created by Nathan W Brei on 2019-04-24.
//

#ifndef JANA2_JPROCESSINGTOPOLOGY_H
#define JANA2_JPROCESSINGTOPOLOGY_H

#include <JANA/JArrow.h>
#include <JANA/JResourcePoolSimple.h>
#include <JANA/JFactorySet.h>
#include <JANA/JEventSourceManager.h>
#include <JANA/JActivable.h>
#include <JANA/JEventProcessor.h>
#include "JPerfMetrics.h"

struct JProcessingTopology : public JActivable {

    using jclock_t = std::chrono::steady_clock;

    enum class StopwatchStatus { BeforeRun, DuringRun, AfterRun };

    explicit JProcessingTopology();
    virtual ~JProcessingTopology();

    JEventSourceManager event_source_manager;
    JResourcePoolSimple<JFactorySet> factoryset_pool;
    std::vector<JFactoryGenerator*> factory_generators;
    std::vector<JEventProcessor*> event_processors;

    std::vector<JArrow*> arrows;
    std::vector<QueueBase*> queues;
    std::vector<JArrow*> sources;           // Sources needed for activation
    std::vector<JArrow*> sinks;             // Sinks needed for finished message count

    JLogger _logger;

    // TODO: These constitute another Metrics object
    StopwatchStatus _stopwatch_status = StopwatchStatus::BeforeRun;
    jclock_t::time_point _start_time;
    jclock_t::time_point _last_time;
    jclock_t::time_point _stop_time;
    size_t _last_message_count = 0;
    size_t _ncpus;

    JPerfMetrics _stopwatch;

    bool is_active() override;
    void set_active(bool is_active) override;
};


#endif //JANA2_JPROCESSINGTOPOLOGY_H
