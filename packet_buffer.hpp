#ifndef __PACKET_BUFFER_H__
#define __PACKET_BUFFER_H__

#include <cstdint>
#include "etl/queue.h"
#include "etl/mutex.h"

constexpr unsigned maxPacketSize = 127u;

struct Packet {
    uint8_t data[maxPacketSize];  // packet data
    uint8_t size=0;               // size of data
};



/**
 * @brief for locking the queue
 * 
 */
void QueueLock()
{
  //todo
  // mtx.lock();
}

/**
 * @brief for unlocking the queue
 * 
 */
void QueueUnlock()
{
  //todo
  // mtx.unlock();
}

enum buffer_status {
    BUFFER_FULL,
    BUFFER_EMPTY,
    BUFFER_OK
};

class packet_buffer {
public:
packet_buffer() = default;
packet_buffer(const packet_buffer&) = delete; // Disable copy constructor
packet_buffer& operator=(const packet_buffer&) = delete; // Disable assignment operator
packet_buffer(packet_buffer&&) = delete; // Disable move constructor
packet_buffer& operator=(packet_buffer&&) = delete; // Disable move assignment operator
public:
    virtual ~packet_buffer() = default;

    /** 
     * @brief Appends a packet to the buffer.
     * @param packet The packet to append.
     * @return buffer_status indicating the result of the operation.
     */
    buffer_status append(const Packet& packet) {
        buffer_status ret = buffer_status::BUFFER_OK;
        QueueLock();
        if (buffer.size() < buffer.max_size()) {
            buffer.push(packet);
            ret = buffer_status::BUFFER_OK;
        }else {
            ret =  buffer_status::BUFFER_FULL;
        }
        QueueUnlock();
        return ret;
    };

    /** 
     * @brief Extracts a packet from the buffer.
     */
    buffer_status extract(Packet* packet) {
        buffer_status ret = buffer_status::BUFFER_OK;
        QueueLock();
        if (buffer.size() > 0) {
            *packet = buffer.front();
            buffer.pop();
            ret = buffer_status::BUFFER_OK;
        }else {
            ret = buffer_status::BUFFER_EMPTY;
        }
        QueueUnlock();
        return ret; 
    };
    /** 
     * @brief Checks if the buffer is full.
     * @return buffer_status indicating the status of the buffer.
     */
    
    virtual buffer_status is_empty() const {
        buffer_status ret = buffer_status::BUFFER_OK;
        if( buffer.empty()) {
            ret =  buffer_status::BUFFER_EMPTY;
        }
        return ret;
    };
    protected:
        etl::queue<Packet,16,etl::memory_model::MEMORY_MODEL_SMALL > buffer;

};



#endif