#pragma once

#include <depthai-shared/common/optional.hpp>
#include <nlohmann/json.hpp>

#include "depthai-shared/common/EepromData.hpp"

namespace dai {

/**
 * Specify properties which apply for whole pipeline
 */
struct GlobalProperties {
    /**
     * Set frequency of Leon OS - Increasing can improve performance, at the cost of higher power
     * draw
     */
    double leonCssFrequencyHz = 700 * 1000 * 1000;
    /**
     * Set frequency of Leon RT - Increasing can improve performance, at the cost of higher power
     * draw
     */
    double leonMssFrequencyHz = 700 * 1000 * 1000;
    tl::optional<std::string> pipelineName;
    tl::optional<std::string> pipelineVersion;
    tl::optional<dai::EepromData> calibData;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GlobalProperties, leonCssFrequencyHz, leonMssFrequencyHz, pipelineName, pipelineVersion, calibData);

}  // namespace dai
