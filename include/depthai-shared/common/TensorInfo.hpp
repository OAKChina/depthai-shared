#pragma once

// std
#include <cstdint>

// project
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

/// TensorInfo structure
struct TensorInfo {
    enum class StorageOrder : int {
        NHWC = 0x4213,
        NHCW = 0x4231,
        NCHW = 0x4321,
        HWC = 0x213,
        CHW = 0x321,
        WHC = 0x123,
        HCW = 0x231,
        WCH = 0x132,
        CWH = 0x312,
        NC = 0x43,
        CN = 0x34,
        C = 0x3,
        H = 0x2,
        W = 0x1,
    };

    enum class DataType : int {
        FP16 = 0,  // Half precision floating point
        U8F = 1,   // Unsigned byte
        INT = 2,   // Signed integer (4 byte)
        FP32 = 3,  // Single precision floating point
        I8 = 4,    // Signed byte
    };

    int getDataTypeSize() {
        switch(dataType) {
            case DataType::U8F:
            case DataType::I8:
                return sizeof(uint8_t);
            case DataType::FP16:
                return sizeof(uint16_t);
            case DataType::INT:
            case DataType::FP32:
                return sizeof(float);
            default:
                return 0;
                break;
        }
    }

    int getWidth() {
        // TODO Don't assume that dims are big enough
        switch(order) {
            case StorageOrder::NHWC:
                return dims[2];
            case StorageOrder::NHCW:
                return dims[3];
            case StorageOrder::NCHW:
                return dims[3];
            case StorageOrder::HWC:
                return dims[1];
            case StorageOrder::CHW:
                return dims[2];
            case StorageOrder::WHC:
                return dims[1];
            case StorageOrder::HCW:
                return dims[2];
            case StorageOrder::WCH:
                return dims[0];
            case StorageOrder::CWH:
                return dims[1];
            case StorageOrder::W:
                return dims[0];
            case StorageOrder::NC:
            case StorageOrder::CN:
            case StorageOrder::C:
            case StorageOrder::H:
            default:
                return 0;
        }
    }

    int getHeight() {
        switch(order) {
            case StorageOrder::NHWC:
                return dims[1];
            case StorageOrder::NHCW:
                return dims[1];
            case StorageOrder::NCHW:
                return dims[2];
            case StorageOrder::HWC:
                return dims[0];
            case StorageOrder::CHW:
                return dims[1];
            case StorageOrder::WHC:
                return dims[1];
            case StorageOrder::HCW:
                return dims[0];
            case StorageOrder::WCH:
                return dims[2];
            case StorageOrder::CWH:
                return dims[2];
            case StorageOrder::H:
                return dims[0];
            case StorageOrder::NC:
            case StorageOrder::CN:
            case StorageOrder::C:
            case StorageOrder::W:
            default:
                return 0;
        }
    }

    int getChannels() {
         switch(order) {
            case StorageOrder::NHWC:
                return dims[3];
            case StorageOrder::NHCW:
                return dims[2];
            case StorageOrder::NCHW:
                return dims[3];
            case StorageOrder::HWC:
                return dims[2];
            case StorageOrder::CHW:
                return dims[0];
            case StorageOrder::WHC:
                return dims[2];
            case StorageOrder::HCW:
                return dims[1];
            case StorageOrder::WCH:
                return dims[1];
            case StorageOrder::CWH:
                return dims[0];
            case StorageOrder::C:
                return dims[0];
            case StorageOrder::NC:
                return dims[1];
            case StorageOrder::CN:
                return dims[0];
            case StorageOrder::H:
            case StorageOrder::W:
            default:
                return 0;
        }
   }

    StorageOrder order = StorageOrder::NCHW;
    DataType dataType = DataType::FP16;
    unsigned int numDimensions = 0;
    std::vector<unsigned> dims;
    std::vector<unsigned> strides;
    std::string name;
    unsigned int offset = 0;

    // Quantisation params (deqValue = (val - qp_zp) * scale )
    bool quantisation = false;
    float qp_scale = 1;
    float qp_zp = 0;
};

DEPTHAI_SERIALIZE_EXT(TensorInfo, order, dataType, numDimensions, dims, strides, name, offset);

}  // namespace dai