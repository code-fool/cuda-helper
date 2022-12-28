#include <string>
#include "cuda-helper/cuda-common.h"

static std::string invalid_msg(int major, int minor) {
    char buf[64];
    sprintf(buf, "Invalid argument (major=%d, minor=%d) of compute capability", major, minor);
    return buf;
}
    
uint32_t smsp_num(int major, int minor) {
    switch (major) {
        case 1: {
            switch (minor) {
                case 0:
                case 1:
                case 2:
                case 3:
                    return 1;
                default:
                    throw std::invalid_argument(invalid_msg(major, minor));
            }
        }
        case 2: {
            switch (minor) {
                case 0:
                case 1:
                    return 1;
                default:
                    throw std::invalid_argument(invalid_msg(major, minor));
            }
        }
        case 3:{
            switch (minor) {
                case 0:
                case 2:
                case 5:
                case 7:
                    return 1;
                default:
                    throw std::invalid_argument(invalid_msg(major, minor));
            }
        }
        case 5: {
            switch (minor) {
                case 0:
                case 2:
                case 3:
                    return 4;
                default:
                    throw std::invalid_argument(invalid_msg(major, minor));
            }
        }
        case 6: {
            switch (minor) {
                case 0: {
                    return 2;
                }
                case 1:
                case 2:{
                    return 4;
                }
                default:
                    throw std::invalid_argument(invalid_msg(major, minor));
            }
        }
        case 7: {
            switch (minor) {
                case 0:
                case 2:
                case 5:
                    return 4;
                default:
                    throw std::invalid_argument(invalid_msg(major, minor));
            }
        }
        case 8: {
            switch (minor) {
                case 0:
                case 6:
                case 7:
                case 9:
                    return 4;
                default:
                    throw std::invalid_argument(invalid_msg(major, minor));
            }
        }
        case 9: {
            switch (minor) {
                case 0:
                    return 4;
                default:
                    throw std::invalid_argument(invalid_msg(major, minor));
            }
        }
        default:
            throw std::invalid_argument(invalid_msg(major, minor));
    }
}