
#include <memory>
#include "gtest/gtest.h"
#include "cuda-helper/cuda-helper.h"
#include "global_variable.h"
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <random>
#include <cuda_runtime.h>

constexpr uint32_t BLAKE3_KEY_LEN = 32;
constexpr uint32_t BLAKE3_OUT_LEN = 32;
constexpr uint32_t BLAKE3_BLOCK_LEN = 64;
constexpr uint32_t BLAKE3_CHUNK_DATA_LEN = 208;
constexpr uint32_t BLAKE3_CHUNK_SIZE = 1024;
constexpr uint32_t NONCE_LEN = 8;
constexpr uint32_t CHUNK_START         = 1 << 0;
constexpr uint32_t CHUNK_END           = 1 << 1;
constexpr uint32_t PARENT              = 1 << 2;
constexpr uint32_t ROOT                = 1 << 3;
constexpr uint32_t KEYED_HASH          = 1 << 4;
constexpr uint32_t DERIVE_KEY_CONTEXT  = 1 << 5;
constexpr uint32_t DERIVE_KEY_MATERIAL = 1 << 6;

constexpr uint32_t LOOP_COUNT = 32;

void fill_random_data(uint8_t *data, uint32_t bytes){
    std::random_device rd;
    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    gen.seed(rd());
    std::uniform_int_distribution<uint8_t> dist(0, 255);

    for (uint32_t i = 0; i < bytes; i++) {
        data[i] = dist(gen);
    }
}

void fill_random_data(uint8_t *data, uint32_t prefix_zero_num, uint32_t bytes){
    if (prefix_zero_num > bytes) {
        throw std::invalid_argument("prefix_zero_num should be less than or equal to bytes");
    }

    std::random_device rd;
    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    gen.seed(rd());
    std::uniform_int_distribution<uint8_t> dist(0, 255);

    for (uint32_t i = 0; i < prefix_zero_num; i++) {
        data[i] = 0;
    }

    for (uint32_t i = prefix_zero_num; i < bytes; i++) {
        data[i] = dist(gen);
    }
}

void print(uint8_t *buf, uint32_t length){
    for (uint32_t i = 0; i < length; i++) {
        printf(" %x", buf[i]);
    }
}

bool bytes_lte(const uint8_t *data, const uint8_t *target, uint32_t length){
    for (uint32_t i = 0; i < length; i++) {
        if (data[i] < target[i]) {
            return true;
        } else if (data[i] > target[i]) {
            return false;
        }
    }
    return true;
}

std::string cur_time_string() {
    time_t current_time;
    struct tm * time_info;

    time(&current_time);
    time_info = localtime(&current_time);
    char time_string[128];
    strftime(time_string, 128, "%F %T", time_info );
    return time_string;
}





TEST(Find, CheckResult) {
    constexpr uint32_t HEADER_BYTES_LEN = 200;
    std::unique_ptr<uint8_t[]> header_bytes(new uint8_t[HEADER_BYTES_LEN]);
    fill_random_data(header_bytes.get(), HEADER_BYTES_LEN);
    //GPU
    cudaDeviceProp prop = device_prop();
    printf("冲冲冲冲冲冲冲冲冲冲冲冲冲冲冲冲冲\n");
    cudaCheckError(cudaSetDeviceFlags(cudaDeviceMapHost))
    uint32_t nonce_buf_len = 1000;
    uint8_t target[BLAKE3_OUT_LEN];
    fill_random_data(target, 4, BLAKE3_OUT_LEN);
}
