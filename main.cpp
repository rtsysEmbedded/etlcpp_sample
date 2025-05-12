#include <iostream>

#include "etl/function.h"
#include "etl/callback_service.h"

#include "etl/mutex.h"
#include "etl/message.h"
#include "etl/message_router.h"
#include"etl/string.h"
#include "etl/queue.h"
#include "packet_buffer.hpp"




int main() {
    etl::string<20> str("Hello, World!");
    etl::queue<Packet,16,etl::memory_model::MEMORY_MODEL_SMALL > buffer;
    std::cout<< str.data() << std::endl;
    return 0;
}

